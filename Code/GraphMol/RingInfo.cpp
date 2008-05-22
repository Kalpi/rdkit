// $Id$
//
//  Copyright (C) 2004-2006 Rational Discovery LLC
//
//   @@ All Rights Reserved  @@
//
#include "RingInfo.h"
#include <RDGeneral/Invariant.h>
#include <algorithm>

namespace RDKit{
  bool RingInfo::isAtomInRingOfSize(unsigned int idx,unsigned int size) const {
    PRECONDITION(df_init,"not initialized");
    PRECONDITION(idx>=0,"bad index");
    if( idx < d_atomMembers.size() ){
      return std::find(d_atomMembers[idx].begin(),d_atomMembers[idx].end(),size)!=d_atomMembers[idx].end();
    } else {
      return false;
    }
  }
  unsigned int RingInfo::minAtomRingSize(unsigned int idx) const {
    PRECONDITION(df_init,"not initialized");
    PRECONDITION(idx>=0,"bad index");
    if( idx < d_atomMembers.size() && d_atomMembers[idx].size() ){
      return *std::min_element(d_atomMembers[idx].begin(),d_atomMembers[idx].end());
    } else {
      return 0;
    }
  }
  unsigned int RingInfo::numAtomRings(unsigned int idx) const {
    PRECONDITION(df_init,"not initialized");
    PRECONDITION(idx>=0,"bad index");
    if( idx < d_atomMembers.size() ){
      return d_atomMembers[idx].size();
    } else {
      return 0;
    }
  }
  bool RingInfo::isBondInRingOfSize(unsigned int idx,unsigned int size) const {
    PRECONDITION(df_init,"not initialized");
    PRECONDITION(idx>=0,"bad index");
    if( idx < d_bondMembers.size() ){
      return std::find(d_bondMembers[idx].begin(),d_bondMembers[idx].end(),size)!=d_bondMembers[idx].end();
    } else {
      return false;
    }

  }
  unsigned int RingInfo::minBondRingSize(unsigned int idx) const {
    PRECONDITION(df_init,"not initialized");
    PRECONDITION(idx>=0,"bad index");
    if( idx < d_bondMembers.size() && d_bondMembers[idx].size() ){
      return *std::min_element(d_bondMembers[idx].begin(),d_bondMembers[idx].end());
    } else {
      return 0;
    }

  }
  unsigned int RingInfo::numBondRings(unsigned int idx) const {
    PRECONDITION(df_init,"not initialized");
    PRECONDITION(idx>=0,"bad index");
    if( idx < d_bondMembers.size() ){
      return d_bondMembers[idx].size();
    } else {
      return 0;
    }
  }

  unsigned int RingInfo::numRings() const {
    PRECONDITION(df_init,"not initialized");
    PRECONDITION(d_atomRings.size()==d_bondRings.size(),"length mismatch");
    return d_atomRings.size();
  }

  unsigned int RingInfo::addRing(const INT_VECT &atomIndices,const INT_VECT &bondIndices){
    PRECONDITION(df_init,"not initialized");
    PRECONDITION(atomIndices.size()==bondIndices.size(),"length mismatch");
    int sz = atomIndices.size();
    for(INT_VECT::const_iterator i=atomIndices.begin();
	i<atomIndices.end(); i++){
      if( *i>=static_cast<int>(d_atomMembers.size()) ) d_atomMembers.resize((*i)+1);
      d_atomMembers[*i].push_back(sz);
    }
    for(INT_VECT::const_iterator i=bondIndices.begin();
	i<bondIndices.end(); i++){
      if( *i>=static_cast<int>(d_bondMembers.size()) ) d_bondMembers.resize((*i)+1);
      d_bondMembers[*i].push_back(sz);
    }
    d_atomRings.push_back(atomIndices);
    d_bondRings.push_back(bondIndices);
    POSTCONDITION(d_atomRings.size()==d_bondRings.size(),"length mismatch");
    return d_atomRings.size();
  }

  void RingInfo::initialize() {
    PRECONDITION(!df_init,"already initialized");
    df_init=true;
  };
  void RingInfo::reset(){
    df_init=false;
    d_atomMembers.clear();
    d_bondMembers.clear();
    d_atomRings.clear();
    d_bondRings.clear();
  }
  void RingInfo::preallocate(unsigned int numAtoms,unsigned int numBonds){
    d_atomMembers.resize(numAtoms);
    d_bondMembers.resize(numBonds);
  }
}
