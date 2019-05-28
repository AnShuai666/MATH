/***********************************************************************
 * Software License Agreement (BSD License)
 *
 * Copyright 2008-2009  Marius Muja (mariusm@cs.ubc.ca). All rights reserved.
 * Copyright 2008-2009  David G. Lowe (lowe@cs.ubc.ca). All rights reserved.
 *
 * THE BSD LICENSE
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *************************************************************************/

#ifndef FLANN_HPP_
#define FLANN_HPP_


#include <vector>
#include <string>
#include <cassert>
#include <cstdio>

#include "general.h"
#include "MATH/flann/util/feature.h"
#include "MATH/flann/util/params.h"
#include "MATH/flann/util/saving.h"

#include "MATH/flann/algorithms/all_indices.h"

namespace flann
{

/**
 * Sets the log level used for all flann functions
 * @param level Verbosity level
 */
inline void log_verbosity(int level)
{
    if (level >= 0) {
        Logger::setLevel(level);
    }
}

/**
 * (Deprecated) Index parameters for creating a saved index.
 */
struct SavedIndexParams : public IndexParams
{
    SavedIndexParams(std::string filename)
    {
        (*this)["algorithm"] = FLANN_INDEX_SAVED;
        (*this)["filename"] = filename;
    }
};



template<typename Distance>
class Index
{
public:
    typedef typename Distance::ElementType ElementType;
    typedef typename Distance::ResultType DistanceType;
    typedef NNIndex<Distance> IndexType;

    Index(const IndexParams& params, Distance distance = Distance() )
        : _index_params(params)
    {
        flann_algorithm_t index_type = get_param<flann_algorithm_t>(params,"algorithm");
        _loaded = false;

        Features<ElementType> features;
        if (index_type == FLANN_INDEX_SAVED) {
            _nnIndex = load_saved_index(features, get_param<std::string>(params,"filename"), distance);
            _loaded = true;
        }
        else {
        	flann_algorithm_t index_type = get_param<flann_algorithm_t>(params, "algorithm");
            _nnIndex = create_index_by_type<Distance>(index_type, features, params, distance);
        }
    }


    Index(const Features<ElementType>& features, const IndexParams& params, Distance distance = Distance() )
        : _index_params(params)
    {
        flann_algorithm_t index_type = get_param<flann_algorithm_t>(params,"algorithm");
        _loaded = false;

        if (index_type == FLANN_INDEX_SAVED) {
            _nnIndex = load_saved_index(features, get_param<std::string>(params,"filename"), distance);
            _loaded = true;
        }
        else {
        	flann_algorithm_t index_type = get_param<flann_algorithm_t>(params, "algorithm");
            _nnIndex = create_index_by_type<Distance>(index_type, features, params, distance);
        }
    }


    Index(const Index& other) : _loaded(other._loaded), _index_params(other._index_params)
    {
    	_nnIndex = other._nnIndex->clone();
    }

    Index& operator=(Index other)
    {
    	this->swap(other);
    	return *this;
    }

    virtual ~Index()
    {
        delete _nnIndex;
    }

    /**
     * Builds the index.
     */
    void buildIndex()
    {
        if (!_loaded) {
            _nnIndex->buildIndex();
        }
    }

    void buildIndex(const Features<ElementType>& points)
    {
    	_nnIndex->buildIndex(points);
    }

    void addPoints(const Features<ElementType>& points, float rebuild_threshold = 2)
    {
        _nnIndex->addPoints(points, rebuild_threshold);
    }

    /**
     * Remove point from the index
     * @param index Index of point to be removed
     */
    void removePoint(size_t point_id)
    {
    	_nnIndex->removePoint(point_id);
    }

    /**
     * Returns pointer to a data point with the specified id.
     * @param point_id the id of point to retrieve
     * @return
     */
    ElementType* getPoint(size_t point_id)
    {
    	return _nnIndex->getPoint(point_id);
    }

    /**
     * Save index to file
     * @param filename
     */
    void save(std::string filename)
    {
        FILE* fout = fopen(filename.c_str(), "wb");
        if (fout == NULL) {
            throw FLANNException("Cannot open file");
        }
        _nnIndex->saveIndex(fout);
        fclose(fout);
    }

    /**
     * \returns number of features in this index.
     */
    size_t veclen() const
    {
        return _nnIndex->veclen();
    }

    /**
     * \returns The dimensionality of the features in this index.
     */
    size_t size() const
    {
        return _nnIndex->size();
    }

    /**
     * \returns The index type (kdtree, kmeans,...)
     */
    flann_algorithm_t getType() const
    {
        return _nnIndex->getType();
    }

    /**
     * \returns The amount of memory (in bytes) used by the index.
     */
    int usedMemory() const
    {
        return _nnIndex->usedMemory();
    }


    /**
     * \returns The index parameters
     */
    IndexParams getParameters() const
    {
        return _nnIndex->getParameters();
    }

    /**
     * \brief Perform k-nearest neighbor search
     * \param[in] queries The query points for which to find the nearest neighbors
     * \param[out] indices The indices of the nearest neighbors found
     * \param[out] dists Distances to the nearest neighbors found
     * \param[in] knn Number of nearest neighbors to return
     * \param[in] params Search parameters
     */
    int knnSearch(const Features<ElementType>& queries,
                                 Features<size_t>& indices,
                                 Features<DistanceType>& dists,
                                 size_t knn,
                           const SearchParams& params) const
    {
    	return _nnIndex->knnSearch(queries, indices, dists, knn, params);
    }

    /**
     *
     * @param queries
     * @param indices
     * @param dists
     * @param knn
     * @param params
     * @return
     */
    int knnSearch(const Features<ElementType>& queries,
                                 Features<int>& indices,
                                 Features<DistanceType>& dists,
                                 size_t knn,
                           const SearchParams& params) const
    {
    	return _nnIndex->knnSearch(queries, indices, dists, knn, params);
    }

    /**
     * \brief Perform k-nearest neighbor search
     * \param[in] queries The query points for which to find the nearest neighbors
     * \param[out] indices The indices of the nearest neighbors found
     * \param[out] dists Distances to the nearest neighbors found
     * \param[in] knn Number of nearest neighbors to return
     * \param[in] params Search parameters
     */
    int knnSearch(const Features<ElementType>& queries,
                                 std::vector< std::vector<size_t> >& indices,
                                 std::vector<std::vector<DistanceType> >& dists,
                                 size_t knn,
                           const SearchParams& params)
    {
    	return _nnIndex->knnSearch(queries, indices, dists, knn, params);
    }

    /**
     *
     * @param queries
     * @param indices
     * @param dists
     * @param knn
     * @param params
     * @return
     */
    int knnSearch(const Features<ElementType>& queries,
                                 std::vector< std::vector<int> >& indices,
                                 std::vector<std::vector<DistanceType> >& dists,
                                 size_t knn,
                           const SearchParams& params) const
    {
    	return _nnIndex->knnSearch(queries, indices, dists, knn, params);
    }

    /**
     * \brief Perform radius search
     * \param[in] queries The query points
     * \param[out] indices The indinces of the neighbors found within the given radius
     * \param[out] dists The distances to the nearest neighbors found
     * \param[in] radius The radius used for search
     * \param[in] params Search parameters
     * \returns Number of neighbors found
     */
    int radiusSearch(const Features<ElementType>& queries,
                                    Features<size_t>& indices,
                                    Features<DistanceType>& dists,
                                    float radius,
                              const SearchParams& params) const
    {
    	return _nnIndex->radiusSearch(queries, indices, dists, radius, params);
    }

    /**
     *
     * @param queries
     * @param indices
     * @param dists
     * @param radius
     * @param params
     * @return
     */
    int radiusSearch(const Features<ElementType>& queries,
                                    Features<int>& indices,
                                    Features<DistanceType>& dists,
                                    float radius,
                              const SearchParams& params) const
    {
    	return _nnIndex->radiusSearch(queries, indices, dists, radius, params);
    }

    /**
     * \brief Perform radius search
     * \param[in] queries The query points
     * \param[out] indices The indinces of the neighbors found within the given radius
     * \param[out] dists The distances to the nearest neighbors found
     * \param[in] radius The radius used for search
     * \param[in] params Search parameters
     * \returns Number of neighbors found
     */
    int radiusSearch(const Features<ElementType>& queries,
                                    std::vector< std::vector<size_t> >& indices,
                                    std::vector<std::vector<DistanceType> >& dists,
                                    float radius,
                              const SearchParams& params) const
    {
    	return _nnIndex->radiusSearch(queries, indices, dists, radius, params);
    }

    /**
     *
     * @param queries
     * @param indices
     * @param dists
     * @param radius
     * @param params
     * @return
     */
    int radiusSearch(const Features<ElementType>& queries,
                                    std::vector< std::vector<int> >& indices,
                                    std::vector<std::vector<DistanceType> >& dists,
                                    float radius,
                              const SearchParams& params) const
    {
    	return _nnIndex->radiusSearch(queries, indices, dists, radius, params);
    }

private:
    IndexType* load_saved_index(const Features<ElementType>& dataset, const std::string& filename, Distance distance)
    {
        FILE* fin = fopen(filename.c_str(), "rb");
        if (fin == NULL) {
            return NULL;
        }
        IndexHeader header = load_header(fin);
        if (header.data_type != flann_datatype_value<ElementType>::value) {
            throw FLANNException("Datatype of saved index is different than of the one to be created.");
        }

        IndexParams params;
        params["algorithm"] = header.index_type;
        IndexType* nnIndex = create_index_by_type<Distance>(header.index_type, dataset, params, distance);
        rewind(fin);
        nnIndex->loadIndex(fin);
        fclose(fin);

        return nnIndex;
    }

    void swap( Index& other)
    {
    	std::swap(_nnIndex, other._nnIndex);
    	std::swap(_loaded, other._loaded);
    	std::swap(_index_params, other._index_params);
    }

private:
    /** Pointer to actual index class */
    IndexType* _nnIndex;
    /** Indices if the index was loaded from a file */
    bool _loaded;
    /** Parameters passed to the index */
    IndexParams _index_params;
};





/**
 * Performs a hierarchical clustering of the points passed as argument and then takes a cut in the
 * the clustering tree to return a flat clustering.
 * @param[in] points Points to be clustered
 * @param centers The computed cluster centres. Features should be preallocated and centers.rows is the
 *  number of clusters requested.
 * @param params Clustering parameters (The same as for flann::KMeansIndex)
 * @param d Distance to be used for clustering (eg: flann::L2)
 * @return number of clusters computed (can be different than clusters.rows and is the highest number
 * of the form (branching-1)*K+1 smaller than clusters.rows).
 */
template <typename Distance>
int hierarchicalClustering(const Features<typename Distance::ElementType>& points, Features<typename Distance::ResultType>& centers,
                           const KMeansIndexParams& params, Distance d = Distance())
{
    KMeansIndex<Distance> kmeans(points, params, d);
    kmeans.buildIndex();

    int clusterNum = kmeans.getClusterCenters(centers);
    return clusterNum;
}

}
#endif /* FLANN_HPP_ */
