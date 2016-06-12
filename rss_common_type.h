/****************************************************************************
 * rss_common_type.h
 *
 *   Copyright (c) 2016 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#ifndef RSS_COMMON_TYPE_H_
#define RSS_COMMON_TYPE_H_

#include <cstdint>

namespace rss {

enum class status_t : uint8_t {
  kSuccess,
  kDownloadFailure,
  kOtherFailure,
  kUnknown
};

}  // namespace rss

#endif  // RSS_COMMON_TYPE_H_

