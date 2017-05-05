///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <QtCore/QDebug>
#include "Inflection.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Crux Namespace ///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Crux
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Crux::Grammar Namespace //////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace Grammar
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Static Properties ////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////

		QMap<QString, QString> Inflection::mIrregular {
				{"move\\z", "moves"},
				{"foot\\z", "feet"},
				{"goose\\z", "geese"},
				{"sex\\z", "sexes"},
				{"child\\z", "children"},
				{"man\\z", "men"},
				{"tooth\\z", "teeth"},
				{"person\\z", "people"},
				{"valve\\z", "valves"}
		};

		QMap<QString, QString> Inflection::mPlural {
				{"(quiz)$\\z", "\\1zes"},
				{"\\A(ox)\\z", "\\1en"},
				{"([m|l])ouse\\z", "\\1ice"},
				{"(matr|vert|ind)ix|ex\\z", "\\1ices"},
				{"(x|ch|ss|sh)\\z", "\\1es"},
				{"([^aeiouy]|qu)y\\z", "\\1ies"},
				{"(hive)\\z", "\1s"},
				{"(?:([^f])fe|([lr])f)\\z", "\\1\\2ves"},
				{"(shea|lea|loa|thie)f\\z", "\\1ves"},
				{"sis\\z", "ses"},
				{"([ti])um\\z", "\1a"},
				{"(tomat|potat|ech|her|vet)o\\z", "\\1oes"},
				{"(bu)s\\z", "\\1ses"},
				{"(alias)\\z", "\\1es"},
				{"(octop)us\\z", "\\1i"},
				{"(ax|test)is\\z", "\\1es"},
				{"(us)\\z", "\\1es"},
				{"s\\z", "s"},
				{"\\z", "s"}
		};

		QMap<QString, QString> Inflection::mSingular {
				{"(quiz)zes\\z", "\\1"},
				{"(matr)ices\\z", "\\1ix"},
				{"(vert|ind)ices\\z", "\\1ex"},
				{"^(ox)en\\z", "\\1"},
				{"(alias)es\\z", "\\1"},
				{"(octop|vir)i\\z", "\\1us"},
				{"(cris|ax|test)es\\z", "\\1is"},
				{"(shoe)s\\z", "\\1"},
				{"(o)es\\z", "\\1"},
				{"(bus)es\\z", "\\1"},
				{"([m|l])ice\\z", "\\1ouse"},
				{"(x|ch|ss|sh)es\\z", "\\1"},
				{"(m)ovies\\z", "\\1ovie"},
				{"(s)eries\\z", "\\1eries"},
				{"([^aeiouy]|qu)ies\\z", "\\1y"},
				{"([lr])ves\\z", "\\1f"},
				{"(tive)s\\z", "\\1"},
				{"(hive)s\\z", "\\1"},
				{"(li|wi|kni)ves\\z", "\\1fe"},
				{"(shea|loa|lea|thie)ves\\z", "\\1f"},
				{"(^analy)ses\\z", "\\1sis"},
				{"((a)naly|(b)a|(d)iagno|(p)arenthe|(p)rogno|(s)ynop|(t)he)ses\\z", "\\1\\2sis"},
				{"([ti])a\\z", "\\1um"},
				{"(n)ews\\z", "\\1ews"},
				{"(h|bl)ouses\\z", "\\1ouse"},
				{"(corpse)s\\z", "\\1"},
				{"(us)es\\z", "\\1"},
				{"(business)\\z", "\\1"},
				{"s\\z", ""}
		};

		QStringList Inflection::mUncountable {
			"sheep", "fish", "deer", "series", "species", "money", "rice", "information", "equipment"
		};

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Public Methods ///////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////

		QString Inflection::pluralize(QString strWord) {
			// Check the uncountable words for the word in question
			if (Inflection::mUncountable.contains(strWord.toLower())) {
				// We're done, return the word
				return strWord;
			}
			// Iterate over the irregular words
			for (QString strKey: Inflection::mIrregular.keys()) {
				// Define the regular expression
				QRegularExpression qreIrregular(strKey, QRegularExpression::DotMatchesEverythingOption|QRegularExpression::CaseInsensitiveOption);
				// Check for the irregular word
				if (qreIrregular.match(strWord).hasMatch()) {
					return strWord.replace(qreIrregular, Inflection::mIrregular.value(strKey));
				}
			}
			// Iterate over the singular patterns
			for (QString strKey: Inflection::mPlural.keys()) {
				// Define the regular expression
				QRegularExpression qrePlural(strKey, QRegularExpression::DotMatchesEverythingOption|QRegularExpression::CaseInsensitiveOption);
				// Check for the singular word
				if (qrePlural.match(strWord).hasMatch()) {
					// Return the modified string
					return strWord.replace(qrePlural, Inflection::mPlural.value(strKey));
				}
			}
			// We're done, return the word
			return strWord;
		}

		QString Inflection::singularize(QString strWord) {
			// Check the uncountable words for the word in question
			if (Inflection::mUncountable.contains(strWord.toLower())) {
				// We're done, return the word
				return strWord;
			}
			// Iterate over the irregular words
			for (QString strKey: Inflection::mIrregular.keys()) {
				// Define the regular expression
				QRegularExpression qreIrregular(strKey, QRegularExpression::CaseInsensitiveOption);
				// Check for the irregular word
				if (qreIrregular.match(strWord).hasMatch()) {
					// Return the replacement
					return strWord.replace(qreIrregular, Inflection::mIrregular.value(strKey));
				}
			}
			// Iterate over the singular patterns
			for (QString strKey: Inflection::mSingular.keys()) {
				// Define the regular expression
				QRegularExpression qreSingular(strKey, QRegularExpression::CaseInsensitiveOption);
				// Check for the singular word
				if (qreSingular.match(strWord).hasMatch()) {
					// Return the modified string
					return strWord.replace(qreSingular, Inflection::mSingular.value(strKey));
				}
			}
			// We're done, return the word
			return strWord;
		}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	} /// End Crux::Grammar Namespace ////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} /// End Crux Namespace /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
