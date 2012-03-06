#ifndef _ALIGNER_H_
#define _ALIGNER_H_

extern "C" {
#include "dataStructures/SR_QueryRegion.h"
#include "outsources/samtools/bam.h"
#include "utilities/bam/SR_BamInStream.h"
#include "utilities/hashTable/SR_HashRegionTable.h"
#include "utilities/hashTable/SR_InHashTable.h"
#include "utilities/hashTable/SR_Reference.h"
}

#include "dataStructures/anchor_region.h"
#include "dataStructures/search_region_type.h"
#include "utilities/smithwaterman/BandedSmithWaterman.h"


struct Alignment;
struct AlignmentFilter;
class HashesCollection;

class Aligner {
 public:
  Aligner(const SR_Reference* reference, 
          const SR_InHashTable* hash_table,
	  const SR_Reference* reference_special,
	  const SR_InHashTable* hash_table_special,
	  const SR_RefHeader* reference_header,
	  const int& fragment_length);
  ~Aligner();
  void AlignCandidate(const bool& detect_special,
                      const AlignmentFilter& alignment_filter,
                      SR_BamInStreamIter* al_ite, 
                      vector<bam1_t*>* alignments);
 private:
  SearchRegionType search_region_type_;
  AnchorRegion     anchor_region_;

  const SR_Reference*   reference_;
  const SR_InHashTable* hash_table_;
  const SR_Reference*   reference_special_;
  const SR_InHashTable* hash_table_special_;
  const SR_RefHeader*   reference_header_;
  SR_QueryRegion*       query_region_;
  HashRegionTable*      hashes_;
  HashRegionTable*      hashes_special_;
  SR_SearchArgs         hash_length_;
  SR_RefView*           special_ref_view_;

  CBandedSmithWaterman  sw_aligner_;

  void LoadRegionType(const bam1_t& anchor);
  const char* GetSequence(const size_t& start, const bool& special) const;
  bool GetAlignment(const HashesCollection& hashes_collection, 
      const unsigned int& id, const bool& special, const int& read_length,
      const char* read_seq, Alignment* al);
  void GetTargetRefRegion(const int& read_length, const int& hash_begin,
      const bool& special, int* begin, int* end);

  Aligner (const Aligner&);
  Aligner& operator= (const Aligner&);
};

#endif // _ALIGNER_H_
