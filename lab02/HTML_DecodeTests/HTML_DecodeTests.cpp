#include "stdafx.h"
#include "../HTML_Decode/HTML_Decode.h"

TEST_CASE("Empty text is converted to empty text", "[HtmlDecode]")
{
	CHECK(HtmlDecode("") == "");
}

TEST_CASE("The text without html characters does not change", "[HtmlDecode]")
{
	CHECK(HtmlDecode("Everything is ok!") == "Everything is ok!");
}

TEST_CASE("All html characters are decoded into a character representation", "[HtmlDecode]")
{
	CHECK(HtmlDecode(R"(Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s)") == R"(Cat <says> "Meow". M&M's)");
}

TEST_CASE("Text without html entities does not change", "[HtmlDecode]")
{
	CHECK(HtmlDecode("Hello&;") == "Hello&;");
}

TEST_CASE("The text with an error in the syntax of html characters does not change", "[HtmlDecode]")
{
	CHECK(HtmlDecode("lt;&lt") == "lt;&lt");
}