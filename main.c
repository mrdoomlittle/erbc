# include <stdio.h>
# include <stdlib.h>
# include <mdlint.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>

char const tmpf_tmpl[] = "/tmp/rbc.XXXXXX";
int main(int __argc, char const *__argv[]) {
	char const *pth = *__argv;
	FILE *fp = fopen(pth, "rb");
	mdl_u32_t off = __OFF;
	mdl_u32_t size;
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, off, SEEK_SET);

	char tmpf_name[sizeof(tmpf_tmpl)];
	strcpy(tmpf_name, tmpf_tmpl);

	int tf_d;
	if ((tf_d = mkstemp(tmpf_name)) < 0) {
		fprintf(stderr, "failed to create tmp file, errno: %d\n", errno);
	}

	mdl_uint_t tf_size = size-off;
	printf("temp file: %s, size: %u bytes.\n", tmpf_name, tf_size);
	mdl_u8_t *raw_bc = (mdl_u8_t*)malloc(tf_size);
	fread(raw_bc, 1, tf_size, fp);
	write(tf_d, raw_bc, tf_size);

	char *argv[] = {"bci", tmpf_name, NULL};
	if (execvp("bci", argv) < 0) {
		fprintf(stderr, "failed, errno: %d\n", errno);
	}

	unlink(tmpf_name);
	fclose(fp);
	free(raw_bc);
}
