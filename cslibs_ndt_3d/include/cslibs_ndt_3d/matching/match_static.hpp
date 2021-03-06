#ifndef MATCH_STATIC_HPP
#define MATCH_STATIC_HPP

#include <cslibs_ndt_3d/matching/match.hpp>
#include <cslibs_ndt_3d/static_maps/gridmap.hpp>

namespace cslibs_ndt_3d {
namespace matching {
namespace static_maps {
inline void match(const cslibs_math_3d::Pointcloud3d::ConstPtr &src,
                  const cslibs_math_3d::Pointcloud3d::ConstPtr &dst,
                  const Parameters                             &params,
                  Result                                       &r)
{
  using ndt_t   = cslibs_ndt_3d::static_maps::Gridmap;
  using size_t  = ndt_t::size_t;
  using index_t = ndt_t::index_t;

  const auto min = dst->min();
  const auto size_m = dst->max() - min;
  const double resolution = params.getResolution();

  const size_t size = {{static_cast<std::size_t>(std::ceil(size_m(0) / resolution)) + 1,
                        static_cast<std::size_t>(std::ceil(size_m(1) / resolution)) + 1,
                        static_cast<std::size_t>(std::ceil(size_m(2) / resolution)) + 1}};
  const index_t min_index = {{static_cast<int>(std::floor(min(0) / resolution)) * 2,
                              static_cast<int>(std::floor(min(1) / resolution)) * 2,
                              static_cast<int>(std::floor(min(2) / resolution)) * 2}};


  ndt_t::Ptr ndt(new ndt_t(ndt_t::pose_t(), params.getResolution(), size, min_index));
  ndt->insert(dst);
  impl::match<ndt_t>(src, ndt, params, r);
}

template<std::size_t Ts>
inline void match(const cslibs_math_3d::Pointcloud3d::ConstPtr &src,
                  const cslibs_math_3d::Pointcloud3d::ConstPtr &dst,
                  const Parameters                             &params,
                  Result                                       &r)
{
  using ndt_t   = cslibs_ndt_3d::static_maps::Gridmap;
  using size_t  = ndt_t::size_t;
  using index_t = ndt_t::index_t;

  const auto   min = dst->min();
  const auto   size_m = dst->max() - min;
  const double resolution = params.getResolution();

  const size_t size = {{static_cast<std::size_t>(std::ceil(size_m(0) / resolution)) + 1,
                        static_cast<std::size_t>(std::ceil(size_m(1) / resolution)) + 1,
                        static_cast<std::size_t>(std::ceil(size_m(2) / resolution)) + 1}};
  const index_t min_index = {{static_cast<int>(std::floor(min(0) / resolution)) * 2,
                              static_cast<int>(std::floor(min(1) / resolution)) * 2,
                              static_cast<int>(std::floor(min(2) / resolution)) * 2}};


  ndt_t::Ptr ndt(new ndt_t(ndt_t::pose_t(), params.getResolution(), size, min_index));
  ndt->insert(dst);
  impl::match<ndt_t, Ts>(src, ndt, params, r);
}
}
}
}

#endif // MATCH_STATIC_HPP
