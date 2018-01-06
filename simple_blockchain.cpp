#include <iostream>
#include <ctime>
#include <unistd.h>
#include <vector>
#include "./PicoSHA2/picosha2.h"

class Block{
public:
	int index_;
	int timestamp_;
	std::string data_;
	std::string previous_hash_;
	std::string hash;

	Block(){index_ = 0; timestamp_ = 0; data_ = ""; previous_hash_ = "";}

	Block(int index, int timestamp, std::string data, std::string previous_hash){
		index_ = index;
		timestamp_ = timestamp;
		data_ = data;
		previous_hash_ = previous_hash;
		hash = GenerateHash();
	}
private:
	std::string GenerateHash(){
		std::string src_str;
		std::string hash_str;

		src_str = std::to_string(index_) + std::to_string(timestamp_) + data_ + previous_hash_;
		picosha2::hash256_hex_string(src_str, hash_str);
		return  hash_str;
	}
public:
	void CheckBlockInfo(){
		std::cout << "index:         " << index_ << std::endl;
		std::cout << "timestamp:     " << timestamp_ << std::endl;
		std::cout << "data:          " << data_ << std::endl;
		std::cout << "previous hash: " << previous_hash_ << std::endl;
		std::cout << "hash:          " << hash << std::endl;
		std::cout << std::endl;
	}
};

Block CreateGenesisBlock(){
	Block genesis_block(0, time(NULL), "Genesis Block", "0");
	return genesis_block;
}

Block CreateGenesisBlock(Block last_block){
	int this_index_ = last_block.index_ + 1;
	int this_timestamp_ = time(NULL);
	std::string this_data_ = "this is block" + std::to_string(this_index_);
	std::string this_hash = last_block.hash;

	Block next_block(this_index_, this_timestamp_, this_data_, this_hash);
	return next_block;
}


int main() {
	std::vector<Block> blockchain;
	Block previous_block;
	Block new_block;

	blockchain.push_back(CreateGenesisBlock());
	previous_block = blockchain[0];


	for(int i=1; i<=5; i++){
		new_block = CreateGenesisBlock(previous_block);
		blockchain.push_back(new_block);
		previous_block = new_block;

		std::cout << "a new block has been added to the blcokchain!" << std::endl;
		new_block.CheckBlockInfo();

		sleep(3);
	}
}
