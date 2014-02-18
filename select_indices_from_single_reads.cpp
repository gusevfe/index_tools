#include <seqan/sequence.h>
#include <seqan/seq_io.h>
#include <seqan/stream.h>
#include <seqan/arg_parse.h>
#include <map>
#include <stdint.h>

using namespace seqan;

int main(int argc, char const* argv[])
{
  uint32_t total_reads = 0;
  uint32_t kept_reads = 0;
  std::map<CharString, bool> keep; // Indices to keep.

  ArgumentParser parser("split_single_reads");

  addUsageLine(parser,
             "-i INDEX [\\fI-i INDEX2\\fP] INPUT1 [\\fIINPUT2\\fP] -O OUTPUT.fastq.gz");

  addDescription(parser,
               "This program allows to select reads with "
               "certain indices from a FASTQ file where "
               "first line of entries look like: \n"
               "  @HISEQ:31:C39VUACXX:4:1101:3194:1985 2:N:0:NAGATN \n"
               "and NAGATN is the index.");

  addOption(parser, seqan::ArgParseOption(
            "i", "index", "Index to select.",
            seqan::ArgParseArgument::STRING, "INDEX", true));

  addOption(parser, seqan::ArgParseOption(
            "O", "output", "Output file.",
            seqan::ArgParseArgument::STRING, "OUTPUT"));

  addArgument(parser, seqan::ArgParseArgument(
        seqan::ArgParseArgument::INPUTFILE, "INPUT", true));  

  // Parse command line.
  ArgumentParser::ParseResult res = parse(parser, argc, argv);
  //
  // Only extract  options if the program will continue after parseCommandLine()
  if (res != ArgumentParser::PARSE_OK)
    return res;

  for (int n = 0; n < getOptionValueCount(parser, "i"); n++) {
    CharString index;
    if (!getOptionValue(index, parser, "i", n)) {
        std::cerr << "ERROR: failed do get index # " << n << "\n";
        return 1;
    }

    keep[index] = true;
  }

  for(int i = 0; i < getArgumentValueCount(parser, 0); ++i) {
    CharString p;
    if(getArgumentValue(p, parser, 0, i) == false) {
        std::cerr << "ERROR: failed do get file # " << i << "\n";
        return 1;
    }

    std::cerr << "INFO: processing file " << p << "\n";

    SequenceStream inStream(toCString(p));

    CharString outputFile;
    if(getOptionValue(outputFile, parser, "O", 0) != true) {
        std::cerr << "ERROR: failed to get output file\n";
        return 1;
    }

    SequenceStream outStream(toCString(outputFile), SequenceStream::WRITE, SequenceStream::FASTQ);
    CharString id;
    Dna5String seq;
    CharString qual;

    while(!atEnd(inStream)) {
      if (readRecord(id, seq, qual, inStream) != 0) {
        std::cerr << "ERROR: failed to read record from " << p << "\n";
        return 1;
      }

      total_reads ++;
      CharString index = suffix(id, length(id) - 6);

      if(keep.find(index) == keep.end())
        continue;

      if(writeRecord(outStream, id, seq, qual) != 0) {
        std::cerr << "ERROR: failed to write record\n";
        return 1;
      }
    
      kept_reads ++;
    }
  }

  std::cerr << "INFO: total_reads = " << total_reads << "\n";
  std::cerr << "INFO: kept_reads = " << 
            kept_reads << " (" << 
            std::setprecision(2) << 
            (kept_reads * 100.0 / total_reads) << ")%\n";
           

  return 0;
}
