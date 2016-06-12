/****************************************************************************
 * libmrss_feed_provider.cc
 *
 *   Copyright (c) 2016 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#include <mrss.h>
#include <cstring>

#include "debug.h"
#include "feed_provider.h"

namespace rss {

FeedProvider::FeedProvider(const std::string& url)
    : is_cached_(false),
      url_(url),
      generic_data_{},
      channel_{},
      items_{} {
  if (ParseFeed() == status_t::kSuccess) is_cached_ = true;
}

GenericData FeedProvider::GetGenericData() const {
  return generic_data_;
}

Channel FeedProvider::GetChannel() const {
  return channel_;
}

std::list<Item> FeedProvider::GetItems() const {
  return items_;
}

bool FeedProvider::HasData() const {
  return is_cached_;
}

status_t FeedProvider::ChangeUrl(const std::string& url) {
  url_ = url;

  if (ParseFeed() == status_t::kSuccess) {
    is_cached_ = true;
  } else {
    is_cached_ = false;
  }
}

status_t FeedProvider::ParseFeed() {
  mrss_t *data;
  mrss_error_t ret;
  if (!strncmp(url_.c_str(), "http://", 7) || !strncmp(url_.c_str(), "https://", 8)) {
    ret = mrss_parse_url_with_options_and_error(const_cast<char *>(url_.c_str()),
                                                &data, nullptr, nullptr);
  } else {
    ret = mrss_parse_file(const_cast<char*>(url_.c_str()), &data);
  }

  DEBUG_PRINTF("parse: %s", mrss_strerror(ret));
  if (ret) {
    if (ret == MRSS_ERR_DOWNLOAD) return status_t::kDownloadFailure;
    return status_t::kOtherFailure;
  }

  // Generic
  generic_data_.file     = data->file;
  generic_data_.encoding = data->encoding;
  generic_data_.size     = static_cast<int32_t>(data->size);
  switch (data->version) {
    case MRSS_VERSION_0_91:
      generic_data_.version = version_t::kRss0_91;
      break;
    case MRSS_VERSION_0_92:
      generic_data_.version = version_t::kRss0_92;
      break;
    case MRSS_VERSION_1_0:
      generic_data_.version = version_t::kRss1_0;
      break;
    case MRSS_VERSION_2_0:
      generic_data_.version = version_t::kRss2_0;
      break;
    case MRSS_VERSION_ATOM_1_0:
      generic_data_.version = version_t::kAtom1_0;
      break;
    case MRSS_VERSION_ATOM_0_3:
      generic_data_.version = version_t::kAtom0_3;
      break;
    default:
      generic_data_.version = version_t::kUnknown;
  }

  // Channel
  channel_.title           = data->title;
  channel_.description     = data->description;
  channel_.link            = data->link;
  channel_.language        = data->language;
  channel_.copyright       = data->copyright;
  channel_.last_build_date = data->lastBuildDate;

  // Items
  auto item = data->item;
  while (item) {
    items_.emplace_back(Item{item->title, item->link, item->description,
                             item->author, item->pubDate});
    item = item->next;
  }

  mrss_free(data);

  return status_t::kSuccess;
}

}  // namespace rss

