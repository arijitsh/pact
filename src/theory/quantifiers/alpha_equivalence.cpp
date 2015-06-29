/*********************                                                        */
/*! \file alpha_equivalence.cpp
 ** \verbatim
 ** Original author: Andrew Reynolds
 ** Major contributors: none
 ** Minor contributors (to current version): none
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2015  New York University and The University of Iowa
 ** See the file COPYING in the top-level source directory for licensing
 ** information.\endverbatim
 **
 ** \brief Alpha equivalence checking
 **
 **/

#include "theory/quantifiers/alpha_equivalence.h"
#include "theory/quantifiers/term_database.h"

using namespace CVC4;
using namespace std;
using namespace CVC4::theory;
using namespace CVC4::theory::quantifiers;
using namespace CVC4::kind;

struct sortTypeOrder {
  TermDb* d_tdb;
  bool operator() (TypeNode i, TypeNode j) {
    return d_tdb->getIdForType( i )<d_tdb->getIdForType( j );
  }
};

bool AlphaEquivalenceNode::registerNode( QuantifiersEngine* qe, Node q, std::vector< Node >& tt, std::vector< int >& arg_index ) {
  if( tt.size()==arg_index.size()+1 ){
    Node t = tt.back();
    Node op = t.hasOperator() ? t.getOperator() : t;
    arg_index.push_back( 0 );
    Trace("aeq-debug") << op << " ";
    return d_children[op][t.getNumChildren()].registerNode( qe, q, tt, arg_index );
  }else if( tt.empty() ){
    //we are finished
    Trace("aeq-debug") << std::endl;
    if( d_quant.isNull() ){
      d_quant = q;
      return true;
    }else{
      //lemma ( q <=> d_quant )
      Trace("alpha-eq") << "Alpha equivalent : " << std::endl;
      Trace("alpha-eq") << "  " << q << std::endl;
      Trace("alpha-eq") << "  " << d_quant << std::endl;
      qe->getOutputChannel().lemma( q.iffNode( d_quant ) );
      return false;
    }
  }else{
    Node t = tt.back();
    int i = arg_index.back();
    if( i==(int)t.getNumChildren() ){
      tt.pop_back();
      arg_index.pop_back();
    }else{
      tt.push_back( t[i] );
      arg_index[arg_index.size()-1]++;
    }
    return registerNode( qe, q, tt, arg_index );
  }
}

bool AlphaEquivalenceTypeNode::registerNode( QuantifiersEngine* qe, Node q, Node t, std::vector< TypeNode >& typs, std::map< TypeNode, int >& typ_count, int index ){
  if( index==(int)typs.size() ){
    std::vector< Node > tt;
    std::vector< int > arg_index;
    tt.push_back( t );
    Trace("aeq-debug") << " : ";
    return d_data.registerNode( qe, q, tt, arg_index );
  }else{
    TypeNode curr = typs[index];
    Assert( typ_count.find( curr )!=typ_count.end() );
    Trace("aeq-debug") << "[" << curr << " " << typ_count[curr] << "] ";
    return d_children[curr][typ_count[curr]].registerNode( qe, q, t, typs, typ_count, index+1 );
  }
}

bool AlphaEquivalence::registerQuantifier( Node q ) {
  Assert( q.getKind()==FORALL );
  Trace("aeq") << "Alpha equivalence : register " << q << std::endl;
  //construct canonical quantified formula
  Node t = d_qe->getTermDatabase()->getCanonicalTerm( q[1], true );
  Trace("aeq") << "  canonical form: " << t << std::endl;
  //compute variable type counts
  std::map< TypeNode, int > typ_count;
  std::vector< TypeNode > typs;
  for( unsigned i=0; i<q[0].getNumChildren(); i++ ){
    TypeNode tn = q[0][i].getType();
    typ_count[tn]++;
    if( std::find( typs.begin(), typs.end(), tn )==typs.end() ){
      typs.push_back( tn );
    }
  }
  sortTypeOrder sto;
  sto.d_tdb = d_qe->getTermDatabase();
  std::sort( typs.begin(), typs.end(), sto );
  Trace("aeq-debug") << "  ";
  bool ret = d_ae_typ_trie.registerNode( d_qe, q, t, typs, typ_count );
  Trace("aeq") << "  ...result : " << ret << std::endl;
  return ret;
}
