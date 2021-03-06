
#ifndef SRC_UTILITIES_BAM_BAMUTILITIES_H_
#define SRC_UTILITIES_BAM_BAMUTILITIES_H_

#include <stdint.h>

#include <string>
#include <vector>

#include "outsources/samtools/bam.h"
#include "utilities/smithwaterman/ssw_cpp.h"

using std::string;
using std::vector;

struct Alignment;

namespace Scissors {
namespace BamUtilities {

bool ReplaceHeaderSoText(bam_header_t* const header);
bool IsFileSorted(const bam_header_t* const header);

// Given sequence, generate bam-format encoded sequence 
// and store it in encodedSequence
void EncodeQuerySequence(string& encodedSequence, const string& sequence);


// Given aligned reference and query sequences,
// generate bam-foramt packed cigar and store it in packed_cigar
bool GetPackedCigar( 
	vector<uint32_t>& packed_cigar, 
	const string& reference,
	const string& query,
	const uint32_t& query_begin,
	const uint32_t& query_end,
	const uint32_t& read_length);

const string ConvertPackedCigarToString(const vector<uint32_t>& packed_cigar);

void CalculateIsize(const bam1_t& myself, const bam1_t& mymate, int* isize);

// For banded SW alignments; we don't use banded SW anymore.
void ConvertAlignmentToBam1(const Alignment& al,
                            const bam1_t& original_record,
			    bam1_t* new_record);

// For SSW alignments
void ConvertAlignmentToBam1(const StripedSmithWaterman::Alignment& al,
                            const bam1_t& original_record,
			    const bool& is_seq_inverse,
			    const bool& is_seq_complement,
			    bam1_t* new_record);

bool AppendReferenceSequence(const char** names,
                             const uint32_t* lens,
			     const char** md5s,
                             const int& n_sequences,
			     bam_header_t* const header);
} // namespace BamUtilities
} // namespace Scirros
#endif // SRC_UTILITIES_BAMUTILITIES_H_
