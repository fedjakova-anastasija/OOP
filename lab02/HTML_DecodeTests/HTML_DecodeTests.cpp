#include "stdafx.h"
#include "../HTML_Decode/HTML_Decode.h"

TEST_CASE("Empty text is converted to empty text", "[HtmlDecode]")
{
	CHECK(HtmlDecode("").empty());
}

TEST_CASE("The text without html entities does not change", "[HtmlDecode]")
{
	CHECK(HtmlDecode("Everything is ok!") == "Everything is ok!");
}

TEST_CASE("The text with html entity &quot; is decoded into a character representation", "[HtmlDecode]")
{
	CHECK(HtmlDecode(R"(Cat says "Meow")") == R"(Cat says "Meow")");
}

TEST_CASE("The text with html entity &apos; is decoded into a character representation", "[HtmlDecode]")
{
	CHECK(HtmlDecode("M&M&apos;s") == "M&M's");
}

TEST_CASE("The text with html entity &lt; is decoded into a character representation", "[HtmlDecode]")
{
	CHECK(HtmlDecode("5&lt;6") == "5<6");
}

TEST_CASE("The text with html entity &gt; is decoded into a character representation", "[HtmlDecode]")
{
	CHECK(HtmlDecode("6&gt;5") == "6>5");

}

TEST_CASE("The text with html entity &amp; is decoded into a character representation", "[HtmlDecode]")
{
	CHECK(HtmlDecode("M&amp;M's)") == "M&M's");
}

TEST_CASE("Text with wrong html entities does not change", "[HtmlDecode]")
{
	CHECK(HtmlDecode("Hello&;") == "Hello&;");
}

TEST_CASE("The text with an error in the syntax of html entities does not change", "[HtmlDecode]")
{
	CHECK(HtmlDecode("lt;&lt") == "lt;&lt");
}