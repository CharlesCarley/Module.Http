#include "Resource.h"

namespace Rt2::HtmlSample
{
   constexpr uint8_t Site[2650]={
           0x3a,0x72,0x6f,0x6f,0x74,0x7b,0x2d,0x2d,0x61,0x2d,0x30,0x3a,0x23,
           0x35,0x30,0x39,0x42,0x44,0x32,0x3b,0x2d,0x2d,0x61,0x2d,0x31,0x3a,
           0x23,0x64,0x32,0x35,0x30,0x38,0x34,0x3b,0x2d,0x2d,0x61,0x2d,0x32,
           0x3a,0x23,0x38,0x34,0x64,0x32,0x35,0x30,0x3b,0x2d,0x2d,0x63,0x2d,
           0x39,0x3a,0x23,0x31,0x37,0x31,0x37,0x31,0x61,0x3b,0x2d,0x2d,0x63,
           0x2d,0x38,0x3a,0x23,0x31,0x62,0x31,0x62,0x31,0x65,0x3b,0x2d,0x2d,
           0x63,0x2d,0x37,0x3a,0x23,0x31,0x66,0x31,0x66,0x32,0x32,0x3b,0x2d,
           0x2d,0x63,0x2d,0x36,0x3a,0x23,0x32,0x33,0x32,0x33,0x32,0x36,0x3b,
           0x2d,0x2d,0x63,0x2d,0x35,0x3a,0x23,0x32,0x37,0x32,0x37,0x32,0x61,
           0x3b,0x2d,0x2d,0x63,0x2d,0x34,0x3a,0x23,0x32,0x62,0x32,0x62,0x32,
           0x65,0x3b,0x2d,0x2d,0x63,0x2d,0x33,0x3a,0x23,0x32,0x66,0x32,0x66,
           0x33,0x32,0x3b,0x2d,0x2d,0x63,0x2d,0x32,0x3a,0x23,0x33,0x33,0x33,
           0x33,0x33,0x36,0x3b,0x2d,0x2d,0x63,0x2d,0x31,0x3a,0x23,0x33,0x37,
           0x33,0x37,0x33,0x61,0x3b,0x2d,0x2d,0x63,0x30,0x3a,0x23,0x33,0x62,
           0x33,0x62,0x33,0x65,0x3b,0x2d,0x2d,0x63,0x31,0x3a,0x23,0x33,0x66,
           0x33,0x66,0x34,0x32,0x3b,0x2d,0x2d,0x63,0x32,0x3a,0x23,0x34,0x33,
           0x34,0x33,0x34,0x36,0x3b,0x2d,0x2d,0x63,0x33,0x3a,0x23,0x34,0x37,
           0x34,0x37,0x34,0x61,0x3b,0x2d,0x2d,0x63,0x34,0x3a,0x23,0x34,0x62,
           0x34,0x62,0x34,0x65,0x3b,0x2d,0x2d,0x63,0x35,0x3a,0x23,0x34,0x66,
           0x34,0x66,0x35,0x32,0x3b,0x2d,0x2d,0x63,0x36,0x3a,0x23,0x35,0x33,
           0x35,0x33,0x35,0x36,0x3b,0x2d,0x2d,0x63,0x37,0x3a,0x23,0x35,0x37,
           0x35,0x37,0x35,0x61,0x3b,0x2d,0x2d,0x63,0x38,0x3a,0x23,0x35,0x62,
           0x35,0x62,0x35,0x65,0x3b,0x2d,0x2d,0x63,0x39,0x3a,0x23,0x35,0x66,
           0x35,0x66,0x36,0x32,0x3b,0x2d,0x2d,0x63,0x32,0x2d,0x39,0x3a,0x23,
           0x37,0x39,0x37,0x36,0x37,0x36,0x3b,0x2d,0x2d,0x63,0x32,0x2d,0x38,
           0x3a,0x23,0x37,0x64,0x37,0x61,0x37,0x61,0x3b,0x2d,0x2d,0x63,0x32,
           0x2d,0x37,0x3a,0x23,0x38,0x31,0x37,0x65,0x37,0x65,0x3b,0x2d,0x2d,
           0x63,0x32,0x2d,0x36,0x3a,0x23,0x38,0x35,0x38,0x32,0x38,0x32,0x3b,
           0x2d,0x2d,0x63,0x32,0x2d,0x35,0x3a,0x23,0x38,0x39,0x38,0x36,0x38,
           0x36,0x3b,0x2d,0x2d,0x63,0x32,0x2d,0x34,0x3a,0x23,0x38,0x64,0x38,
           0x61,0x38,0x61,0x3b,0x2d,0x2d,0x63,0x32,0x2d,0x33,0x3a,0x23,0x39,
           0x31,0x38,0x65,0x38,0x65,0x3b,0x2d,0x2d,0x63,0x32,0x2d,0x32,0x3a,
           0x23,0x39,0x35,0x39,0x32,0x39,0x32,0x3b,0x2d,0x2d,0x63,0x32,0x2d,
           0x31,0x3a,0x23,0x39,0x39,0x39,0x36,0x39,0x36,0x3b,0x2d,0x2d,0x63,
           0x32,0x30,0x3a,0x23,0x39,0x64,0x39,0x61,0x39,0x61,0x3b,0x2d,0x2d,
           0x63,0x32,0x31,0x3a,0x23,0x61,0x31,0x39,0x65,0x39,0x65,0x3b,0x2d,
           0x2d,0x63,0x32,0x32,0x3a,0x23,0x61,0x35,0x61,0x32,0x61,0x32,0x3b,
           0x2d,0x2d,0x63,0x32,0x33,0x3a,0x23,0x61,0x39,0x61,0x36,0x61,0x36,
           0x3b,0x2d,0x2d,0x63,0x32,0x34,0x3a,0x23,0x61,0x64,0x61,0x61,0x61,
           0x61,0x3b,0x2d,0x2d,0x63,0x32,0x35,0x3a,0x23,0x62,0x31,0x61,0x65,
           0x61,0x65,0x3b,0x2d,0x2d,0x63,0x32,0x36,0x3a,0x23,0x62,0x35,0x62,
           0x32,0x62,0x32,0x3b,0x2d,0x2d,0x63,0x32,0x37,0x3a,0x23,0x62,0x39,
           0x62,0x36,0x62,0x36,0x3b,0x2d,0x2d,0x63,0x32,0x38,0x3a,0x23,0x62,
           0x64,0x62,0x61,0x62,0x61,0x3b,0x2d,0x2d,0x63,0x32,0x39,0x3a,0x23,
           0x63,0x31,0x62,0x65,0x62,0x65,0x7d,0x2e,0x62,0x2d,0x39,0x7b,0x62,
           0x61,0x63,0x6b,0x67,0x72,0x6f,0x75,0x6e,0x64,0x2d,0x63,0x6f,0x6c,
           0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x2d,0x39,0x29,
           0x7d,0x2e,0x66,0x2d,0x39,0x7b,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,
           0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x2d,0x39,0x29,0x7d,0x2e,0x62,
           0x63,0x2d,0x39,0x7b,0x62,0x6f,0x72,0x64,0x65,0x72,0x2d,0x63,0x6f,
           0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x2d,
           0x39,0x29,0x7d,0x2e,0x62,0x2d,0x38,0x7b,0x62,0x61,0x63,0x6b,0x67,
           0x72,0x6f,0x75,0x6e,0x64,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,
           0x61,0x72,0x28,0x2d,0x2d,0x63,0x2d,0x38,0x29,0x7d,0x2e,0x66,0x2d,
           0x38,0x7b,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,
           0x2d,0x63,0x32,0x2d,0x38,0x29,0x7d,0x2e,0x62,0x63,0x2d,0x38,0x7b,
           0x62,0x6f,0x72,0x64,0x65,0x72,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,
           0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x2d,0x38,0x29,0x7d,0x2e,
           0x62,0x2d,0x37,0x7b,0x62,0x61,0x63,0x6b,0x67,0x72,0x6f,0x75,0x6e,
           0x64,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,
           0x2d,0x63,0x2d,0x37,0x29,0x7d,0x2e,0x66,0x2d,0x37,0x7b,0x63,0x6f,
           0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x2d,
           0x37,0x29,0x7d,0x2e,0x62,0x63,0x2d,0x37,0x7b,0x62,0x6f,0x72,0x64,
           0x65,0x72,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,
           0x2d,0x2d,0x63,0x32,0x2d,0x37,0x29,0x7d,0x2e,0x62,0x2d,0x36,0x7b,
           0x62,0x61,0x63,0x6b,0x67,0x72,0x6f,0x75,0x6e,0x64,0x2d,0x63,0x6f,
           0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x2d,0x36,
           0x29,0x7d,0x2e,0x66,0x2d,0x36,0x7b,0x63,0x6f,0x6c,0x6f,0x72,0x3a,
           0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x2d,0x36,0x29,0x7d,0x2e,
           0x62,0x63,0x2d,0x36,0x7b,0x62,0x6f,0x72,0x64,0x65,0x72,0x2d,0x63,
           0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,
           0x2d,0x36,0x29,0x7d,0x2e,0x62,0x2d,0x35,0x7b,0x62,0x61,0x63,0x6b,
           0x67,0x72,0x6f,0x75,0x6e,0x64,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,
           0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x2d,0x35,0x29,0x7d,0x2e,0x66,
           0x2d,0x35,0x7b,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,
           0x2d,0x2d,0x63,0x32,0x2d,0x35,0x29,0x7d,0x2e,0x62,0x63,0x2d,0x35,
           0x7b,0x62,0x6f,0x72,0x64,0x65,0x72,0x2d,0x63,0x6f,0x6c,0x6f,0x72,
           0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x2d,0x35,0x29,0x7d,
           0x2e,0x62,0x2d,0x34,0x7b,0x62,0x61,0x63,0x6b,0x67,0x72,0x6f,0x75,
           0x6e,0x64,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,
           0x2d,0x2d,0x63,0x2d,0x34,0x29,0x7d,0x2e,0x66,0x2d,0x34,0x7b,0x63,
           0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,
           0x2d,0x34,0x29,0x7d,0x2e,0x62,0x63,0x2d,0x34,0x7b,0x62,0x6f,0x72,
           0x64,0x65,0x72,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,
           0x28,0x2d,0x2d,0x63,0x32,0x2d,0x34,0x29,0x7d,0x2e,0x62,0x2d,0x33,
           0x7b,0x62,0x61,0x63,0x6b,0x67,0x72,0x6f,0x75,0x6e,0x64,0x2d,0x63,
           0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x2d,
           0x33,0x29,0x7d,0x2e,0x66,0x2d,0x33,0x7b,0x63,0x6f,0x6c,0x6f,0x72,
           0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x2d,0x33,0x29,0x7d,
           0x2e,0x62,0x63,0x2d,0x33,0x7b,0x62,0x6f,0x72,0x64,0x65,0x72,0x2d,
           0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,
           0x32,0x2d,0x33,0x29,0x7d,0x2e,0x62,0x2d,0x32,0x7b,0x62,0x61,0x63,
           0x6b,0x67,0x72,0x6f,0x75,0x6e,0x64,0x2d,0x63,0x6f,0x6c,0x6f,0x72,
           0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x2d,0x32,0x29,0x7d,0x2e,
           0x66,0x2d,0x32,0x7b,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,
           0x28,0x2d,0x2d,0x63,0x32,0x2d,0x32,0x29,0x7d,0x2e,0x62,0x63,0x2d,
           0x32,0x7b,0x62,0x6f,0x72,0x64,0x65,0x72,0x2d,0x63,0x6f,0x6c,0x6f,
           0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x2d,0x32,0x29,
           0x7d,0x2e,0x62,0x2d,0x31,0x7b,0x62,0x61,0x63,0x6b,0x67,0x72,0x6f,
           0x75,0x6e,0x64,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,
           0x28,0x2d,0x2d,0x63,0x2d,0x31,0x29,0x7d,0x2e,0x66,0x2d,0x31,0x7b,
           0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,
           0x32,0x2d,0x31,0x29,0x7d,0x2e,0x62,0x63,0x2d,0x31,0x7b,0x62,0x6f,
           0x72,0x64,0x65,0x72,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,
           0x72,0x28,0x2d,0x2d,0x63,0x32,0x2d,0x31,0x29,0x7d,0x2e,0x62,0x30,
           0x7b,0x62,0x61,0x63,0x6b,0x67,0x72,0x6f,0x75,0x6e,0x64,0x2d,0x63,
           0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x30,
           0x29,0x7d,0x2e,0x66,0x30,0x7b,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,
           0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x30,0x29,0x7d,0x2e,0x62,0x63,
           0x30,0x7b,0x62,0x6f,0x72,0x64,0x65,0x72,0x2d,0x63,0x6f,0x6c,0x6f,
           0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x30,0x29,0x7d,
           0x2e,0x62,0x31,0x7b,0x62,0x61,0x63,0x6b,0x67,0x72,0x6f,0x75,0x6e,
           0x64,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,
           0x2d,0x63,0x31,0x29,0x7d,0x2e,0x66,0x31,0x7b,0x63,0x6f,0x6c,0x6f,
           0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x31,0x29,0x7d,
           0x2e,0x62,0x63,0x31,0x7b,0x62,0x6f,0x72,0x64,0x65,0x72,0x2d,0x63,
           0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,
           0x31,0x29,0x7d,0x2e,0x62,0x32,0x7b,0x62,0x61,0x63,0x6b,0x67,0x72,
           0x6f,0x75,0x6e,0x64,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,
           0x72,0x28,0x2d,0x2d,0x63,0x32,0x29,0x7d,0x2e,0x66,0x32,0x7b,0x63,
           0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,
           0x32,0x29,0x7d,0x2e,0x62,0x63,0x32,0x7b,0x62,0x6f,0x72,0x64,0x65,
           0x72,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,
           0x2d,0x63,0x32,0x32,0x29,0x7d,0x2e,0x62,0x33,0x7b,0x62,0x61,0x63,
           0x6b,0x67,0x72,0x6f,0x75,0x6e,0x64,0x2d,0x63,0x6f,0x6c,0x6f,0x72,
           0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x33,0x29,0x7d,0x2e,0x66,
           0x33,0x7b,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,
           0x2d,0x63,0x32,0x33,0x29,0x7d,0x2e,0x62,0x63,0x33,0x7b,0x62,0x6f,
           0x72,0x64,0x65,0x72,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,
           0x72,0x28,0x2d,0x2d,0x63,0x32,0x33,0x29,0x7d,0x2e,0x62,0x34,0x7b,
           0x62,0x61,0x63,0x6b,0x67,0x72,0x6f,0x75,0x6e,0x64,0x2d,0x63,0x6f,
           0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x34,0x29,
           0x7d,0x2e,0x66,0x34,0x7b,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,
           0x72,0x28,0x2d,0x2d,0x63,0x32,0x34,0x29,0x7d,0x2e,0x62,0x63,0x34,
           0x7b,0x62,0x6f,0x72,0x64,0x65,0x72,0x2d,0x63,0x6f,0x6c,0x6f,0x72,
           0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x34,0x29,0x7d,0x2e,
           0x62,0x35,0x7b,0x62,0x61,0x63,0x6b,0x67,0x72,0x6f,0x75,0x6e,0x64,
           0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,
           0x63,0x35,0x29,0x7d,0x2e,0x66,0x35,0x7b,0x63,0x6f,0x6c,0x6f,0x72,
           0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x35,0x29,0x7d,0x2e,
           0x62,0x63,0x35,0x7b,0x62,0x6f,0x72,0x64,0x65,0x72,0x2d,0x63,0x6f,
           0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x35,
           0x29,0x7d,0x2e,0x62,0x36,0x7b,0x62,0x61,0x63,0x6b,0x67,0x72,0x6f,
           0x75,0x6e,0x64,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,
           0x28,0x2d,0x2d,0x63,0x36,0x29,0x7d,0x2e,0x66,0x36,0x7b,0x63,0x6f,
           0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x36,
           0x29,0x7d,0x2e,0x62,0x63,0x36,0x7b,0x62,0x6f,0x72,0x64,0x65,0x72,
           0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,
           0x63,0x32,0x36,0x29,0x7d,0x2e,0x62,0x37,0x7b,0x62,0x61,0x63,0x6b,
           0x67,0x72,0x6f,0x75,0x6e,0x64,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,
           0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x37,0x29,0x7d,0x2e,0x66,0x37,
           0x7b,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,
           0x63,0x32,0x37,0x29,0x7d,0x2e,0x62,0x63,0x37,0x7b,0x62,0x6f,0x72,
           0x64,0x65,0x72,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,
           0x28,0x2d,0x2d,0x63,0x32,0x37,0x29,0x7d,0x2e,0x62,0x38,0x7b,0x62,
           0x61,0x63,0x6b,0x67,0x72,0x6f,0x75,0x6e,0x64,0x2d,0x63,0x6f,0x6c,
           0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x38,0x29,0x7d,
           0x2e,0x66,0x38,0x7b,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,
           0x28,0x2d,0x2d,0x63,0x32,0x38,0x29,0x7d,0x2e,0x62,0x63,0x38,0x7b,
           0x62,0x6f,0x72,0x64,0x65,0x72,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,
           0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x38,0x29,0x7d,0x2e,0x62,
           0x39,0x7b,0x62,0x61,0x63,0x6b,0x67,0x72,0x6f,0x75,0x6e,0x64,0x2d,
           0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,
           0x39,0x29,0x7d,0x2e,0x66,0x39,0x7b,0x63,0x6f,0x6c,0x6f,0x72,0x3a,
           0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x39,0x29,0x7d,0x2e,0x62,
           0x63,0x39,0x7b,0x62,0x6f,0x72,0x64,0x65,0x72,0x2d,0x63,0x6f,0x6c,
           0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x39,0x29,
           0x7d,0x62,0x6f,0x64,0x79,0x7b,0x70,0x61,0x64,0x64,0x69,0x6e,0x67,
           0x3a,0x30,0x3b,0x6d,0x61,0x72,0x67,0x69,0x6e,0x3a,0x30,0x3b,0x62,
           0x61,0x63,0x6b,0x67,0x72,0x6f,0x75,0x6e,0x64,0x2d,0x63,0x6f,0x6c,
           0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x30,0x29,0x7d,
           0x61,0x7b,0x74,0x65,0x78,0x74,0x2d,0x64,0x65,0x63,0x6f,0x72,0x61,
           0x74,0x69,0x6f,0x6e,0x3a,0x6e,0x6f,0x6e,0x65,0x7d,0x2e,0x6c,0x31,
           0x7b,0x64,0x69,0x73,0x70,0x6c,0x61,0x79,0x3a,0x66,0x6c,0x65,0x78,
           0x3b,0x66,0x6c,0x65,0x78,0x2d,0x64,0x69,0x72,0x65,0x63,0x74,0x69,
           0x6f,0x6e,0x3a,0x63,0x6f,0x6c,0x75,0x6d,0x6e,0x3b,0x6d,0x69,0x6e,
           0x2d,0x68,0x65,0x69,0x67,0x68,0x74,0x3a,0x31,0x35,0x25,0x7d,0x2e,
           0x6c,0x30,0x7b,0x66,0x6c,0x65,0x78,0x2d,0x67,0x72,0x6f,0x77,0x3a,
           0x31,0x7d,0x2e,0x6f,0x66,0x2d,0x30,0x7b,0x6f,0x76,0x65,0x72,0x66,
           0x6c,0x6f,0x77,0x3a,0x68,0x69,0x64,0x64,0x65,0x6e,0x7d,0x2e,0x6f,
           0x66,0x2d,0x31,0x7b,0x6f,0x76,0x65,0x72,0x66,0x6c,0x6f,0x77,0x3a,
           0x61,0x75,0x74,0x6f,0x7d,0x2e,0x6f,0x66,0x2d,0x78,0x7b,0x6f,0x76,
           0x65,0x72,0x66,0x6c,0x6f,0x77,0x2d,0x79,0x3a,0x68,0x69,0x64,0x64,
           0x65,0x6e,0x3b,0x6f,0x76,0x65,0x72,0x66,0x6c,0x6f,0x77,0x2d,0x78,
           0x3a,0x61,0x75,0x74,0x6f,0x7d,0x2e,0x6f,0x66,0x2d,0x79,0x7b,0x6f,
           0x76,0x65,0x72,0x66,0x6c,0x6f,0x77,0x2d,0x78,0x3a,0x68,0x69,0x64,
           0x64,0x65,0x6e,0x3b,0x6f,0x76,0x65,0x72,0x66,0x6c,0x6f,0x77,0x2d,
           0x79,0x3a,0x61,0x75,0x74,0x6f,0x7d,0x2e,0x66,0x61,0x2d,0x32,0x7b,
           0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,
           0x32,0x35,0x29,0x7d,0x2e,0x66,0x61,0x2d,0x31,0x7b,0x63,0x6f,0x6c,
           0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x39,0x29,
           0x7d,0x2e,0x66,0x61,0x30,0x7b,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,
           0x61,0x72,0x28,0x2d,0x2d,0x61,0x2d,0x30,0x29,0x7d,0x2e,0x66,0x61,
           0x31,0x7b,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,
           0x2d,0x61,0x2d,0x31,0x29,0x7d,0x2e,0x66,0x61,0x32,0x7b,0x63,0x6f,
           0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x63,0x32,0x2d,
           0x35,0x29,0x7d,0x2e,0x62,0x61,0x30,0x7b,0x62,0x61,0x63,0x6b,0x67,
           0x72,0x6f,0x75,0x6e,0x64,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,
           0x61,0x72,0x28,0x2d,0x2d,0x61,0x2d,0x30,0x29,0x7d,0x2e,0x62,0x61,
           0x31,0x7b,0x62,0x61,0x63,0x6b,0x67,0x72,0x6f,0x75,0x6e,0x64,0x2d,
           0x63,0x6f,0x6c,0x6f,0x72,0x3a,0x76,0x61,0x72,0x28,0x2d,0x2d,0x61,
           0x2d,0x31,0x29,0x7d,0x2e,0x62,0x61,0x32,0x7b,0x62,0x61,0x63,0x6b,
           0x67,0x72,0x6f,0x75,0x6e,0x64,0x2d,0x63,0x6f,0x6c,0x6f,0x72,0x3a,
           0x76,0x61,0x72,0x28,0x2d,0x2d,0x61,0x2d,0x32,0x29,0x7d,
   };

   void Resource::getSite(ByteArray &dest)
   {
       dest.write(Site, 2650);
   }

   void Resource::getSite(String &dest)
   {
       dest.assign((const char *)Site, 2650);
   }
} // namespace Rt2::HtmlSample
