#include <huffman.h>


int main()
{
	char buffer[1000] = "fdfdfdfgjkfjkgrutrtrtkgfkgjjfdfsdiruiedfffdffgffg";
	char huffman[1000];
	Coding htable[256];
	int nbit, bytes;
	nbit = compress(buffer, huffman, htable);
	bytes = decompress(huffman, nbit, htable, buffer);
	buffer[bytes] = '\0';
	printf("%s\n", buffer);
	compressFile("hello.txt", "huffman.dat");
	decompressFile("huffman.dat", "hello_new.txt");
	return 0;
}
