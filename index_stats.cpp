#include <seqan/sequence.h>
#include <seqan/seq_io.h>
#include <seqan/stream.h>
#include <map>
#include <stdint.h>

using namespace seqan;

int main(int argc, char const* argv[])
{
  uint32_t total_reads = 0;
  std::map<CharString, uint32_t> counts;

  for(int i = 1; i < argc; ++i) {
    char const *p = argv[i];

    std::cerr << "Processing file " << p << "\n";

    SequenceStream seqStream(p);
    CharString id;
    Dna5String seq;
    CharString qual;

    while(!atEnd(seqStream)) {
      if (readRecord(id, seq, qual, seqStream) != 0) {
        std::cerr << "ERROR: failed to read record from " << p << "\n";
        return 1;
      }

      total_reads ++;
      CharString index = suffix(id, length(id) - 6);
      counts[index] ++;
    }
  }

  std::cerr << "Total reads processed = " << total_reads << "\n";

  std::cout << std::setprecision(2);

  std::map<CharString, uint32_t>::const_iterator i = counts.begin();
  for(; i != counts.end(); ++i) {
    std::cout << i->first << "\t" 
              << i->second << "\t" 
              << 100 * double(i->second) / double(total_reads) << "\n";
  }

  return 0;
}
