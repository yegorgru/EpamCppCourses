#include "ReadFile.h"

#include <fstream>
#include <iostream>

void read_file_exceptions(const std::string& path) {
	try
	{
	std::ifstream fin(path, std::ios::ate);
	if (!fin.is_open()) {
		throw FileOpenFailed();
	}
	else {
		long size = fin.tellg();
		if (size <= 0) {
			throw SizeDeterminationFailed();
		}
		else {
			std::string fileData;
			fileData.reserve(size);
			if (fileData.capacity() < size) {
				throw MemoryAllocationFailed();
			}
			else {
				try
				{
					fin.seekg(0, std::ios::beg);
					fileData = std::string((std::istreambuf_iterator<char>(fin)),
						std::istreambuf_iterator<char>());
					std::cout << fileData << std::endl;
				}
				catch (const std::exception&)
				{
					throw ReadFailed();
				}
			}
		}
		fin.close();
		if (fin.is_open()) {
			throw FileCloseFailed();
		}
	}
	}
	catch (const FileOpenFailed& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (const SizeDeterminationFailed& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (const MemoryAllocationFailed& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (const ReadFailed& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (const FileCloseFailed& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

ErrorCode read_file_error_codes(const std::string& path) {
	auto code = ErrorCode::SuccessfullyRead;
	std::ifstream fin(path, std::ios::ate);
	if (!fin.is_open()) {
		code = ErrorCode::FileOpenFailed;
	}
	else {
		long size = fin.tellg();
		if (size <= 0) {
			code = ErrorCode::SizeDeterminationFailed;
		}
		else {
			std::string fileData;
			fileData.reserve(size);
			if (fileData.capacity() < size) {
				code = ErrorCode::MemoryAllocationFailed;
			}
			else {
				try
				{
					fin.seekg(0, std::ios::beg);
					fileData = std::string((std::istreambuf_iterator<char>(fin)),
						std::istreambuf_iterator<char>());
					std::cout << fileData << std::endl;
				}
				catch (const std::exception&)
				{
					code = ErrorCode::ReadFailed;
				}
			}
		}
		fin.close();
		if (fin.is_open() && code == ErrorCode::SuccessfullyRead) {
			code = ErrorCode::FileCloseFailed;
		}
	}
	return code;
}

const char* FileOpenFailed::what() const noexcept {
	return "Can't open file";
}

const char* SizeDeterminationFailed::what() const noexcept {
	return "Can't determine size of file";
}

const char* MemoryAllocationFailed::what() const noexcept {
	return "Can't allocate memory";
}

const char* ReadFailed::what() const noexcept {
	return "Can't read file";
}

const char* FileCloseFailed::what() const noexcept {
	return "Can't close file";
}