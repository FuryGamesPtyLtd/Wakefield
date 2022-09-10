#pragma once

#include "CoreMinimal.h"

// #include <time.h>

#include <chrono>
// #include <ctime>
// #include <iomanip>
// #include <sstream>
// #include <string>

using FWkfDuration = std::chrono::duration<int64_t, std::nano>;
using FWkfTimePoint = std::chrono::time_point<std::chrono::system_clock, FWkfDuration>;

// namespace std::chrono {
// 	inline std::ostream& operator<<(std::ostream& o, FDuration duration) {
// 		return o << duration.count() << "ns";
// 	}
// }  // namespace std::chrono

inline double ToSeconds(FWkfDuration duration) {
	return static_cast<double>(duration.count()) / 1.0e9;
}

// namespace std::chrono {
// 	inline std::ostream& operator<<(std::ostream& o, FTimePoint time_point) {
// 		std::time_t time = std::chrono::system_clock::to_time_t(
// 			std::chrono::time_point_cast<std::chrono::system_clock::duration>(
// 				time_point));
// 		std::tm result;
// 		#ifdef PLATFORM_WINDOWS
// 		::localtime_s(&result, &time);
// 		#else
// 		::localtime_r(&time, &result);
// 		#endif
//
// 		return o << std::put_time(&result, "%F %T");
// 	}
// }  // namespace std::chrono

// inline FString ToFilenameString(FTimePoint time_point) {
// 	std::string s1 = Enstring(time_point);
// 	std::string s2;
// 	for (char c : s1)
// 		if (std::isdigit(c)) s2 += c;
// 	return s2;
// }

inline FWkfTimePoint Now() {
	return std::chrono::time_point_cast<FWkfDuration>(
		std::chrono::system_clock::now());
}
