#ifndef Decompress_H
#define Decompress_H

#include "Common.h"
#include "Stats.h"
#include "Parsers/BAMParser.h"
#include "Parsers/SAMParser.h"
#include "Fields/Sequence.h"
#include "Fields/ReadName.h"
#include "Fields/MappingFlag.h"
#include "Fields/EditOperation.h"
#include "Fields/MappingQuality.h"
#include "Fields/QualityScore.h"
#include "Fields/PairedEnd.h"
#include "Fields/OptionalField.h"

class FileDecompressor {
	SequenceDecompressor *sequence;
	EditOperationDecompressor *editOp;
	ReadNameDecompressor *readName;
	MappingFlagDecompressor *mapFlag;
	MappingQualityDecompressor *mapQual;
	QualityScoreDecompressor *quality;
	PairedEndDecompressor *pairedEnd;
	OptionalFieldDecompressor *optField;

	FILE *samFile;
	FILE *inFile;
	gzFile idxFile;
	
	Stats *stats;
	size_t inFileSz;
    size_t blockSize;

public:
	static void printStats (const std::string &inFile, int filterFlag);

public:
	FileDecompressor (const std::string &inFile, const std::string &outFile, const std::string &genomeFile, int bs);
	~FileDecompressor (void);

private:
	void getMagic (void);
	void getComment (bool output);
	size_t getBlock (const std::string &chromosome, size_t start, size_t end, int filterFlag);
	void readBlock (Decompressor *d, Array<uint8_t> &in);

public:
	void decompress (int filterFlag);
	void decompress (const std::string &idxFilePath, const std::string &range, int filterFlag);
};

#endif // Decompress_H