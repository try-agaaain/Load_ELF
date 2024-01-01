#include <iostream>
#include <fstream>
#include <vector>
#include <elf.h>       // 注意在你的系统中找到这个头文件
using namespace std;


// 用于打开文件，读取内容
vector<char> readFile(const string& filename) {
    ifstream file(filename, ios::binary);
    
    return vector<char>((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

#include <iomanip> // 用于 std::setw 和 std::setfill
#include <iostream>

void displayElfHeader(const Elf64_Ehdr& hdr) {
    std::cout << "ELF Header:\n";

    // Magic字段的打印
    std::cout << "  Magic:   ";
    for (int i = 0; i < EI_NIDENT; ++i) {
        std::cout << std::hex << std::uppercase 
                  << std::setw(2) << std::setfill('0') 
                  << static_cast<int>(hdr.e_ident[i]) << " ";
    }
    std::cout << "\n";

    // 类型ELF64
    std::cout << "  Class:                             ELF64\n";
    // 数据类型，2'补码，小端模式
    std::cout << "  Data:                              2's complement, little endian\n";
    // 当前版本
    std::cout << "  Version:                           1 (current)\n";
    // OS/ABI 类型，UNIX - System V
    std::cout << "  OS/ABI:                            UNIX - System V\n";
    // ABI 版本
    std::cout << "  ABI Version:                       0\n";

    // 打印其他字段
    std::cout << "  Type:                              " << std::dec << hdr.e_type << "\n";
    std::cout << "  Machine:                           " << std::dec << hdr.e_machine << "\n";
    std::cout << "  Version:                           " << std::dec << hdr.e_version << "\n";
    std::cout << "  Entry point address:               " << std::hex << hdr.e_entry << "\n";
    std::cout << "  Start of program headers:          " << std::dec << hdr.e_phoff << " (bytes into file)\n";
    std::cout << "  Start of section headers:          " << std::dec << hdr.e_shoff << " (bytes into file)\n";
    std::cout << "  Flags:                             " << std::hex << hdr.e_flags << "\n";
    std::cout << "  Size of this header:               " << std::dec << hdr.e_ehsize << " (bytes)\n";
    std::cout << "  Size of program headers:           " << std::dec << hdr.e_phentsize << " (bytes)\n";
    std::cout << "  Number of program headers:         " << std::dec << hdr.e_phnum << "\n";
    std::cout << "  Size of section headers:           " << std::dec << hdr.e_shentsize << " (bytes)\n";
    std::cout << "  Number of section headers:         " << std::dec << hdr.e_shnum << "\n";
    std::cout << "  Section header string table index: " << std::dec << hdr.e_shstrndx << "\n";
}

void displayProgramHeader(const Elf64_Ehdr& hdr, char* start) {
	auto* phdr_start = reinterpret_cast<Elf64_Phdr*>(start + hdr.e_phoff);

	for (int i = 0; i < hdr.e_phnum; i++) {
		std::cout << "  Type           Offset             VirtAddr           PhysAddr" << std::endl;
		std::cout << "                 FileSiz            MemSiz              Flags  Align" << std::endl;

		auto& phdr = *(phdr_start + i);
		std::cout << "  " << phdr.p_type << "           " << phdr.p_offset << " " << phdr.p_vaddr
				<< " " << phdr.p_paddr << std::endl;
		std::cout << "                 " << phdr.p_filesz << "            " << phdr.p_memsz 
				<< "  " << phdr.p_flags << "  " << phdr.p_align << std::endl;

		// Continue printing the rest based on the `phdr.p_type`
	}
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cerr << "Usage: " << argv[0] << " <ELF_FILE>\n";
        return 1;
    }

    vector<char> fileData = readFile(argv[1]);

	Elf64_Ehdr hdr = *reinterpret_cast<Elf64_Ehdr*>(fileData.data());
	displayElfHeader(hdr);
	displayProgramHeader(hdr, fileData.data());

    return 0;
}
