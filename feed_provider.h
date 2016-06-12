/****************************************************************************
 * feed_provider.cc
 *
 *   Copyright (c) 2016 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#ifndef FEED_PROVIDER_H_
#define FEED_PROVIDER_H_

#include <cstdint>
#include <list>
#include <string>

#include "rss_common_type.h"

namespace rss {

enum class version_t : uint8_t {
  kRss0_91,
  kRss0_92,
  kRss1_0,
  kRss2_0,
  kAtom1_0,
  kAtom0_3,
  kUnknown,
};

struct GenericData {
  std::string file;
  std::string encoding;
  int32_t size;
  version_t version;
};

struct Channel {
  std::string title;
  std::string description;
  std::string link;
  std::string language;
  std::string copyright;
  std::string last_build_date;
};

struct Item {
  std::string title;
  std::string link;
  std::string description;
  std::string author;
  std::string pub_date;
};

class FeedProvider final {
 public:
  explicit FeedProvider(const std::string& url);
  ~FeedProvider() = default;

  GenericData     GetGenericData() const;
  Channel         GetChannel()     const;
  std::list<Item> GetItems()       const;
  bool HasData() const;
  status_t ChangeUrl(const std::string& url);

 private:
  bool is_cached_;
  std::string url_;
  GenericData generic_data_;
  Channel channel_;
  std::list<Item> items_;

  status_t ParseFeed();
};

}  // namespace rss

#endif  // FEED_PROVIDER_H_

