/* ************************************************************************** */
/*                                                                            */
/*   printdump.c                                                              */
/*                                                                            */
/*   By: Rashoru-Infinity <65536toaru@gmail.com>                              */
/*                                                                            */
/*   Created: 2021/09/05 04:05:41 by Rashoru-Infinity                         */
/*   Updated: 2021/09/05 04:05:41 by Rashoru-Infinity                         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OUT_BUF_SIZE 65536
#define	HEX_LENGTH 50
#define	WORD 16
#define BYTE 8
#define TAB_STOP 8
#define ADDR_STR_LENGTH 20

static void buffered_write(char *s, int len, int flush) {
	static char buf[OUT_BUF_SIZE];
	static size_t offset;

	if (len < 0)
		len = 0;
	if (s && len + offset < OUT_BUF_SIZE && !flush) {
		memcpy(buf + offset, s, len);
		offset += len;
	} else if (flush) {
		write(1, buf, offset);
		if (s)
			write(1, s, len);
		memset(buf, 0, offset);
		offset = 0;
	} else {
		write(1, buf, offset);
		memset(buf, 0, offset);
		offset = 0;
		if (s) {
			memcpy(buf, s, len);
			offset += len;
		}
	}
}

static void write_ascii(char *s, size_t len) {
	char *buf;
	size_t offset;

	if (!(buf = malloc(sizeof(char) * (len + 1))))
		return ;
	memcpy(buf, s, len);
	offset = 0;
	while (offset < len) {
		if ((unsigned char)(buf[offset]) < 0x20 || (unsigned char)(buf[offset]) > 0x7e)
			buf[offset] = '.';
		offset++;
	}
	buf[offset] = '\n';
	buffered_write(buf, len + 1, 0);
	free(buf);
}

int main(int argc, char **argv) {
	char msb4, lsb4;
	char line[HEX_LENGTH];
	char read_buf[WORD];
	char addr_str[ADDR_STR_LENGTH];
	int next = 0;
	int cnt;
	int read_size;
	FILE *file;
	void *address;
	int tab_cnt;

	if (argc != 2) {
		printf("Usage : %s [file]\n", argv[0]);
		exit(0);
	}
	if (!(file = fopen(argv[1], "r"))) {
		printf("fail to open file\n");
		exit(1);
	}
	address = 0;
	while (!feof(file)) {
		next = 0;
		memset(addr_str, 0, ADDR_STR_LENGTH);
		memset(line, 0, HEX_LENGTH);
		memset(read_buf, 0, WORD);
		if (address)
			sprintf(addr_str, "%p", address);
		else
			sprintf(addr_str, "0x00");
		memset(addr_str + strlen(addr_str), '\t', strlen(addr_str) % 8 ?
		(TAB_STOP * 3 - strlen(addr_str)) / TAB_STOP + 1
		: (TAB_STOP * 3 - strlen(addr_str)) / TAB_STOP);
		read_size = fread(read_buf, sizeof(char), WORD, file);
		if (ferror(file)) {
			printf("fail to read file\n");
			exit(1);
		}
		if (!read_size)
			break ;
		cnt = 0;
		while (cnt < read_size) {
			msb4 = (unsigned char)(read_buf[cnt]) >> 4;
			lsb4 = read_buf[cnt] & 0xf;
			if (msb4 >= 10)
				msb4 = 'a' + msb4 - 10;
			else
				msb4 += '0';
			if (lsb4 >= 10)
				lsb4 = 'a' + lsb4 - 10;
			else
				lsb4 += '0';
			line[next++] = msb4;
			line[next++] = lsb4;
			if (next != BYTE * 3 - 1)
				line[next++] = ' ';
			else if (read_size > BYTE)
				line[next++] = '-';
			else
				line[next] = ' ';
			cnt++;
		}
		tab_cnt = (WORD * 3 + TAB_STOP - read_size * 3) / TAB_STOP;
		if (read_size % TAB_STOP)
			tab_cnt++;
		memset(line + strlen(line), '\t', tab_cnt);
		buffered_write(addr_str, strlen(addr_str), 0);
		buffered_write(line, strlen(line), 0);
		write_ascii(read_buf, read_size);
		address += 0x10;
	}
	buffered_write(NULL, 0, 1);
	fclose(file);
}
