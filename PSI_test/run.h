#pragma once

int runmock(int x);

int run(uint64_t senderSize,
	uint64_t receiverSize,
	uint64_t logHeight,
	uint64_t hashLengthInBytes,
	uint64_t bucket,
	std::string ip,
	int role);