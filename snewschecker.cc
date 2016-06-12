/****************************************************************************
 * snewschecker.cc
 *
 *   Copyright (c) 2016 Yoshinori Sugino
 *   This software is released under the MIT License.
 ****************************************************************************/
#include <cstdlib>
#include <iostream>

#include "feed_provider.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "ERROR" << std::endl;
    return EXIT_FAILURE;
  }

  rss::FeedProvider feed(argv[1]);

  if (feed.HasData() == false) {
    std::cout << "ERROR" << std::endl;
    return EXIT_FAILURE;
  }

  auto generic_data = feed.GetGenericData();
  std::cout << "-- Generic Data --" << std::endl;
  std::cout << "file: "     << generic_data.file     << std::endl;
  std::cout << "encoding: " << generic_data.encoding << std::endl;
  std::cout << "size: "     << generic_data.size     << std::endl;
  std::cout << "version: ";
  switch (generic_data.version) {
    case rss::version_t::kRss0_91:
      std::cout << "Rss 0.91";
      break;
    case rss::version_t::kRss0_92:
      std::cout << "Rss 0.92";
      break;
    case rss::version_t::kRss1_0:
      std::cout << "Rss 1.0";
      break;
    case rss::version_t::kRss2_0:
      std::cout << "Rss 2.0";
      break;
    case rss::version_t::kAtom1_0:
      std::cout << "Atom 1.0";
      break;
    case rss::version_t::kAtom0_3:
      std::cout << "Atom 0.3";
      break;
    default:
      std::cout << "Unknown";
  }
  std::cout << std::endl;

  std::cout << std::endl;
  auto channel = feed.GetChannel();
  std::cout << "-- Channel --" << std::endl;
  std::cout << "title: "         << channel.title           << std::endl;
  std::cout << "description: "   << channel.description     << std::endl;
  std::cout << "link: "          << channel.link            << std::endl;
  std::cout << "language: "      << channel.language        << std::endl;
  std::cout << "copyright: "     << channel.copyright       << std::endl;
  std::cout << "lastBuildDate: " << channel.last_build_date << std::endl;

  std::cout << std::endl;
  std::cout << "-- Items --" << std::endl;
  auto items = feed.GetItems();
  for (auto item : items) {
    std::cout << "title: " << item.title << std::endl;
  }

  return EXIT_SUCCESS;
}

