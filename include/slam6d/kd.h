/** @file 
 *  @brief Representation of the optimized k-d tree. 
 *  @author Andreas Nuechter. Institute of Computer Science, University of Osnabrueck, Germany.
 *  @author Kai Lingemann. Institute of Computer Science, University of Osnabrueck, Germany.
 *  @author Thomas Escher
 */

#ifndef __KD_H__
#define __KD_H__

#include "slam6d/kdparams.h"
#include "slam6d/searchTree.h"
#include "slam6d/kdTreeImpl.h"

#ifdef _MSC_VER
#if !defined _OPENMP && defined OPENMP 
#define _OPENMP
#endif
#endif

#ifdef _OPENMP
#include <omp.h>
#endif


struct Void { };

struct PtrAccessor {
    inline double *operator() (Void, double* indices) {
        return indices;
    }
};

/**
 * @brief The optimized k-d tree. 
 * 
 * A kD tree for points, with limited
 * capabilities (find nearest point to
 * a given point, or to a ray).
 **/
class KDtree : public SearchTree, private KDTreeImpl<Void, double*, PtrAccessor> {
public:
  KDtree(double **pts, int n);
  
  virtual ~KDtree();

  virtual double *FindClosest(double *_p, double maxdist2, int threadNum = 0) const;
  virtual void FindClosestKNNRange(double *_p, double maxdist2, std::vector<double *>& closest_list, size_t knn = 0, int threadNum = 0) const;
};

#endif
