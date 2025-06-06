/*
 * Generated by ./misc/optlib2c from optlib/scdoc.ctags, Don't edit this manually.
 */
#include "general.h"
#include "parse.h"
#include "routines.h"
#include "field.h"
#include "xtag.h"


typedef enum {
	K_TITLE,
	K_SECTION,
	K_SUBSECTION,
} ScdocKind;


static void initializeScdocParser (const langType language)
{
	addLanguageOptscriptToHook (language, SCRIPT_HOOK_SEQUEL,
		"{{    clear\n"
		"}}");

	addLanguageRegexTable (language, "init");
	addLanguageRegexTable (language, "main");
	addLanguageRegexTable (language, "section");
	addLanguageRegexTable (language, "fini");
	addLanguageRegexTable (language, "comment");
	addLanguageRegexTable (language, "skipline");

	addLanguageTagMultiTableRegex (language, "init",
	                               "^;([^\n]*[\n]|[^\n]+)",
	                               "", "", "", NULL);
	addLanguageTagMultiTableRegex (language, "init",
	                               "^([^\\( ]+)\\([^\n]*[\n]?",
	                               "\\1", "t", "{scope=push}{tenter=main}"
		"{{\n"
		"   .\n"
		"}}", NULL);
	addLanguageTagMultiTableRegex (language, "init",
	                               "^[^\n]*\n",
	                               "", "", "", NULL);
	addLanguageTagMultiTableRegex (language, "init",
	                               "^[^\n]+",
	                               "", "", "", NULL);
	addLanguageTagMultiTableRegex (language, "main",
	                               "^##([^\n]*\n|[^\n]+)",
	                               "", "", "", NULL);
	addLanguageTagMultiTableRegex (language, "main",
	                               "^#[ \t]*([^\n]+)[ ]*[\n]?",
	                               "\\1", "s", "{scope=push}{tenter=section}"
		"{{\n"
		"   count 2 eq { @1 _matchloc2line 1 sub end: } if\n"
		"   .\n"
		"}}", NULL);
	addLanguageTagMultiTableRegex (language, "main",
	                               "^[^\n]*\n",
	                               "", "", "", NULL);
	addLanguageTagMultiTableRegex (language, "main",
	                               "^[^\n]+",
	                               "", "", "", NULL);
	addLanguageTagMultiTableRegex (language, "main",
	                               "^()",
	                               "", "", "{scope=pop}{_advanceTo=0start}{tleave}", NULL);
	addLanguageTagMultiTableRegex (language, "section",
	                               "^##[ \t]*([^\n]+)[ ]*[\n]?",
	                               "\\1", "S", "{scope=ref}"
		"{{\n"
		"   count 3 eq { @1 _matchloc2line 1 sub end: } if\n"
		"   .\n"
		"}}", NULL);
	addLanguageTagMultiTableRegex (language, "section",
	                               "^#[ \t]*([^\n]+)[ ]*[\n]?",
	                               "", "", "{scope=pop}{_advanceTo=0start}{tleave}"
		"{{\n"
		"   count 3 eq { @1 _matchloc2line 1 sub end: } if\n"
		"}}", NULL);
	addLanguageTagMultiTableRegex (language, "section",
	                               "^[^\n]*\n",
	                               "", "", "", NULL);
	addLanguageTagMultiTableRegex (language, "section",
	                               "^[^\n]+",
	                               "", "", "", NULL);
	addLanguageTagMultiTableRegex (language, "section",
	                               "^()",
	                               "", "", "{scope=pop}{_advanceTo=0start}{tleave}"
		"{{\n"
		"   count 3 eq { @1 _matchloc2line end: } if\n"
		"}}", NULL);
	addLanguageTagMultiTableRegex (language, "comment",
	                               "^;([^\n]*[\n]|[^\n]+)",
	                               "", "", "", NULL);
	addLanguageTagMultiTableRegex (language, "skipline",
	                               "^[^\n]*\n",
	                               "", "", "", NULL);
	addLanguageTagMultiTableRegex (language, "skipline",
	                               "^[^\n]+",
	                               "", "", "", NULL);
}

extern parserDefinition* ScdocParser (void)
{
	static const char *const extensions [] = {
		"scd",
		NULL
	};

	static const char *const aliases [] = {
		NULL
	};

	static const char *const patterns [] = {
		NULL
	};

	static kindDefinition ScdocKindTable [] = {
		{
		  true, 't', "title", "titles",
		},
		{
		  true, 's', "section", "sections",
		},
		{
		  true, 'S', "subsection", "sub sections",
		},
	};

	parserDefinition* const def = parserNew ("Scdoc");

	def->versionCurrent= 0;
	def->versionAge    = 0;
	def->enabled       = true;
	def->extensions    = extensions;
	def->patterns      = patterns;
	def->aliases       = aliases;
	def->method        = METHOD_NOT_CRAFTED|METHOD_REGEX;
	def->useCork       = CORK_QUEUE;
	def->kindTable     = ScdocKindTable;
	def->kindCount     = ARRAY_SIZE(ScdocKindTable);
	def->defaultScopeSeparator = "\"\"";
	def->initialize    = initializeScdocParser;

	return def;
}
