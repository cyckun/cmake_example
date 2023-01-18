#include "PSI/include/Defines.h"
#include "PSI/include/utils.h"
#include "PSI/include/PsiSender.h"
#include "PSI/include/PsiReceiver.h"
#include "run.h"

#include <cryptoTools/Network/IOService.h>
#include <cryptoTools/Network/Endpoint.h>
#include <cryptoTools/Network/Channel.h>
#include <cryptoTools/Common/CLP.h>
#include <cryptoTools/Common/Log.h>

#include <vector>
#include <iostream>

using namespace std;
using namespace PSI;

const block commonSeed = oc::toBlock(123456);

u64 senderSize;
u64 receiverSize;
u64 width;
u64 height;
u64 logHeight;
u64 hashLengthInBytes;
u64 bucket, bucket1, bucket2;
string ip;


void runSender() {
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Server, "test-psi");
	Channel ch = ep.addChannel();

	vector<block> senderSet(senderSize); 
	PRNG prng(oc::toBlock(123));
	for (auto i = 0; i < senderSize; ++i) {
		senderSet[i] = prng.get<block>();
	}
	
	PsiSender psiSender;
	psiSender.run(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, senderSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}

void runReceiver() {
	IOService ios;
	Endpoint ep(ios, ip, EpMode::Client, "test-psi");
	Channel ch = ep.addChannel();

	vector<block> receiverSet(receiverSize); 
	PRNG prng(oc::toBlock(123));
	for (auto i = 0; i < 100; ++i) {
		receiverSet[i] = prng.get<block>();
	}
	
	PRNG prng2(oc::toBlock(456));
	for (auto i = 100; i < receiverSize; ++i) {
		receiverSet[i] = prng2.get<block>();
	}
	
	PsiReceiver psiReceiver;
	psiReceiver.run(prng, ch, commonSeed, senderSize, receiverSize, height, logHeight, width, receiverSet, hashLengthInBytes, 32, bucket1, bucket2);
	
	ch.close();
	ep.stop();
	ios.stop();
}


int runmock(int x) {
	// std::cout << "this PSI_test lib." << std::endl;
	return 2*x;
}


int run(u64 senderSize,
	u64 receiverSize,
	u64 logHeight,
	u64 hashLengthInBytes,
	u64 bucket,
	string ip,
	int role) {
	
	
	senderSize = senderSize;
	
	receiverSize = receiverSize;
	width = 600;
	logHeight = logHeight;
	height = 1 << logHeight;

	hashLengthInBytes = 10;
	ip = ip;
	

	std::cout
		<< "=================================\n"
		<< "||  Private Set Intersection   ||\n"
		<< "=================================\n"
		<< "\n"
		<< "This program reports the performance of the private set intersection protocol.\n"
		<< "\n"
		<< "Experimenet flag:\n"
		<< " -r 0    to run a sender.\n"
		<< " -r 1    to run a receiver.\n"
		<< "\n"
		<< "Parameters:\n"
		<< " -ss     log(#elements) on sender side.\n"
		<< " -rs     log(#elements) on receiver side.\n"
		<< " -w      width of the matrix.\n"
		<< " -h      log(height) of the matrix.\n"
		<< " -hash   hash output length in bytes.\n"
		<< " -ip     ip address (and port).\n"
		;

	if (role == 0) {
		runSender();
	} else if (role == 1) {
		runReceiver();
	}

	return 0;
}




