///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CRUX_CORE_IS_HPP
#define CRUX_CORE_IS_HPP

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <QtCore/QObject>
#include <QtCore/QString>
#include <typeinfo>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Crux Namespace ///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Crux
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Crux::Core Namespace /////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace Core
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Crux::Core::Is Class Definition //////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////

		class Is : public QObject
		{
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Qt Object Recognition ////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			Q_OBJECT

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Public Methods & Properties //////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			public:

				///////////////////////////////////////////////////////////////////////////////////////////////////////
				/// Qt Determinants //////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////

				/**
				 * @paragraph This method determines whether or not the variable is a QBitArray
				 * @access public
				 * @name Crux::Core::Is::bitArray()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool bitArray(TTest mixTest)       { return QString(typeid(mixTest).name()).contains("QBitArray");         }

				/**
				 * @paragraph This method determines whether or not the variable is a QByteArray
				 * @access public
				 * @name Crux::Core::Is::byteArray()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool byteArray(TTest mixTest)      { return QString(typeid(mixTest).name()).contains("QByteArray");        }

				/**
				 * @paragraph This method determines whether or not the variable is a QBitArrayList
				 * @access public
				 * @name Crux::Core::Is::byteArrayList()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool byteArrayList(TTest mixTest)  { return QString(typeid(mixTest).name()).contains("QByteArrayList");    }

				/**
				 * @paragraph This method determines whether or not the variable is a QChar
				 * @access public
				 * @name Crux::Core::Is::character()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool character(TTest mixTest)      { return QString(typeid(mixTest).name()).contains("QChar");             }

				/**
				 * @paragraph This method determines whether or not the variable is a QHash
				 * @access public
				 * @name Crux::Core::Is::hash()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool hash(TTest mixTest)           { return QString(typeid(mixTest).name()).contains("QHash");             }

				/**
				 * @paragraph This method determines whether or not the variable is a QJsonArray
				 * @access public
				 * @name Crux::Core::Is::jsonArray()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool jsonArray(TTest mixTest)      { return QString(typeid(mixTest).name()).contains("QJsonArray");        }

				/**
				 * @paragraph This method determines whether or not the variable is a QJsonDocument
				 * @access public
				 * @name Crux::Core::Is::jsonDocument()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool jsonDocument(TTest mixTest)   { return QString(typeid(mixTest).name()).contains("QJsonDocument");     }

				/**
				 * @paragraph This method determines whether or not the variable is a QJsonObject
				 * @access public
				 * @name Crux::Core::Is::jsonObject()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool jsonObject(TTest mixTest)     { return QString(typeid(mixTest).name()).contains("QJsonObject");       }

				/**
				 * @paragraph This method determines whether or not the variable is a QJsonValue
				 * @access public
				 * @name Crux::Core::Is::jsonValue()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool jsonValue(TTest mixTest)      { return QString(typeid(mixTest).name()).contains("QJsonValue");        }

				/**
				 * @paragraph This method determines whether or not the variable is a QList
				 * @access public
				 * @name Crux::Core::Is::list()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool list(TTest mixTest)           { return QString(typeid(mixTest).name()).contains("QList");             }

				/**
				 * @paragraph This method determines whether or not the variable is a QMap
				 * @access public
				 * @name Crux::Core::Is::map()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool map(TTest mixTest)            { return QString(typeid(mixTest).name()).contains("QMap");             }

				/**
				 * @paragraph This method determines whether or not the variable is a QObject
				 * @access public
				 * @name Crux::Core::Is::object()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool object(TTest mixTest)         { return QString(typeid(mixTest).name()).contains("QObject");          }

				/**
				 * @paragraph This method determines whether or not the variable is a QString
				 * @access public
				 * @name Crux::Core::Is::string()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool string(TTest mixTest)         { return QString(typeid(mixTest).name()).contains("QString");          }

				/**
				 * @paragraph This method determines whether or not the variable is a QStringList
				 * @access public
				 * @name Crux::Core::Is::stringList()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool stringList(TTest mixTest)     { return QString(typeid(mixTest).name()).contains("QStringList");      }

				/**
				 * @paragraph This method determines whether or not the variable is a QVariant
				 * @access public
				 * @name Crux::Core::Is::variant()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool variant(TTest mixTest)        { return QString(typeid(mixTest).name()).contains("QVariant");         }

				/**
				 * @paragraph This method determines whether or not the variable is a QVariantHash
				 * @access public
				 * @name Crux::Core::Is::variantHash()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool variantHash(TTest mixTest)    { return QString(typeid(mixTest).name()).contains("QVariantHash");     }

				/**
				 * @paragraph This method determines whether or not the variable is a QVariantList
				 * @access public
				 * @name Crux::Core::Is::variantList()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool variantList(TTest mixTest)    { return QString(typeid(mixTest).name()).contains("QVariantList");     }

				/**
				 * @paragraph This method determines whether or not the variable is a QVariantMap
				 * @access public
				 * @name Crux::Core::Is::variantMap()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool variantMap(TTest mixTest)     { return QString(typeid(mixTest).name()).contains("QVariantMap");      }

				/**
				 * @paragraph This method determines whether or not the variable is a QVector
				 * @access public
				 * @name Crux::Core::Is::vector()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool vector(TTest mixTest)         { return QString(typeid(mixTest).name()).contains("QVector");          }

				///////////////////////////////////////////////////////////////////////////////////////////////////////
				/// Standard Determinants ////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////

				/**
				 * @paragraph This method determines whether or not the variable is a char
				 * @access public
				 * @name Crux::Core::Is::basicCharacter()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool basicCharacter(TTest mixTest) { return (typeid(mixTest).name() == "c");                              }

				/**
				 * @paragraph This method determines whether or not the variable is a double
				 * @access public
				 * @name Crux::Core::Is::basicDouble()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool basicDouble(TTest mixTest)    { return (typeid(mixTest).name() == "d");                              }

				/**
				 * @paragraph This method determines whether or not the variable is a float
				 * @access public
				 * @name Crux::Core::Is::basicFloat()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool basicFloat(TTest mixTest)     { return (typeid(mixTest).name() == "f");                              }

				/**
				 * @paragraph This method determines whether or not the variable is a int
				 * @access public
				 * @name Crux::Core::Is::basicInt()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool basicInt(TTest mixTest)       { return (typeid(mixTest).name() == "i");                              }

				/**
				 * @paragraph This method determines whether or not the variable is an std::string
				 * @access public
				 * @name Crux::Core::Is::basicString()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool basicString(TTest mixTest)    { return QString(typeid(mixTest).name()).contains("basic_string");     }

				/**
				 * @paragraph This method determines whether or not the variable is a boolean
				 * @access public
				 * @name Crux::Core::Is::boolean()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool boolean(TTest mixTest)        { return (typeid(mixTest).name() == "b");                              }

				///////////////////////////////////////////////////////////////////////////////////////////////////////
				/// Grouped Determinants /////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////

				/**
				 * @paragraph This method determines whether or not the variable is a form of string
				 * @access public
				 * @name Crux::Core::Is::literal()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool literal(TTest mixTest)        { return (string(mixTest) || character(mixTest) || byteArray(mixTest) || basicString(mixTest)); }

				/**
				 * @paragraph This method determines whether or not the variable is numeric
				 * @access public
				 * @name Crux::Core::Is::number()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool number(TTest mixTest)         { return (basicInt(mixTest) || basicDouble(mixTest) || basicFloat(mixTest));                    }

				/**
				 * @paragraph This method determines whether or not the variable is numeric, boolean or a string
				 * @access public
				 * @name Crux::Core::Is::scalar()
				 * @namespace Crux::Core
				 * @param TTest mixTest
				 * @return bool
				 * @static
				 */
				template <typename TTest>
				inline static bool scalar(TTest mixTest)         { return (boolean(mixTest) || literal(mixTest) || number(mixTest));                             }

				///////////////////////////////////////////////////////////////////////////////////////////////////////
				/// Pointer Determinants /////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////



		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}; /// End Crux::Core::Is Class Definition ///////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	} /// End Crux::Core Namespace ///////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} /// End Crux Namespace /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif /// End Definitions ///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
