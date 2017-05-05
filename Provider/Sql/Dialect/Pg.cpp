///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Pg.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Crux Namespace ///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Crux
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Crux::Provider Namespace /////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace Provider
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Crux::Provider::Sql Namespace ////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////

		namespace Sql
		{
			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Crux::Provider::Sql::Dialect Namespace ///////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			namespace Dialect
			{
				///////////////////////////////////////////////////////////////////////////////////////////////////////
				/// Factory //////////////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////

				Pg *Pg::Factory(QString strName, QString strDatabase, QString strUsername, QString strPassword, QString strHost, int intPort) {
					// Return the new instance
					return new Pg(strName, strDatabase, strUsername, strPassword, strHost, intPort);
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////
				/// Constructor //////////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////

				Pg::Pg(QString strName, QString strDatabase, QString strUsername, QString strPassword, QString strHost, int intPort) {
					// Set the driver into the instance
					this->setDriver(Driver::PostgreSQL);
					// Set the database name into the instance
					this->setDatabase(strDatabase);
					// Set the database's authentication username into the instance
					this->setUsername(strUsername);
					// Set the database's authentication password into the instance
					this->setPassword(strPassword);
					// Set the connection name into the instance
					this->setName(strName);
					// Set the database's host name into the instance
					this->setHost(strHost);
					// Set the database's port number into the instance
					this->setPort(intPort);
					// Open the connection
					this->connect();
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////
				/// Implementations //////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////

				QMap<QString, QVector<QString>> Pg::describe(QString strTable, QString strSchema) {
					// Define our description container
					QMap<QString, QVector<QString>> mapDescription;
					// Define the describe statement
					QString strDescribeStatement = "SELECT DISTINCT \"c\".\"column_name\", \"c\".\"data_type\", \"c\".\"column_default\", \"c\".\"is_nullable\", CASE WHEN \"i\".\"constraint_type\" = 'PRIMARY KEY' THEN 'PRI' ELSE \"i\".\"constraint_type\" END AS \"column_key\" FROM \"information_schema\".\"columns\" AS \"c\" LEFT JOIN \"information_schema\".\"key_column_usage\" AS \"k\" ON (\"k\".\"column_name\" = \"c\".\"column_name\") LEFT JOIN \"information_schema\".\"table_constraints\" AS \"i\" ON (\"i\".\"constraint_catalog\" = \"c\".\"table_catalog\" AND \"i\".\"constraint_schema\" = \"c\".\"table_schema\" AND \"i\".\"constraint_name\" = \"k\".\"constraint_name\") WHERE \"c\".\"table_catalog\" = '%s' AND \"c\".\"table_schema\" = '%s' AND \"c\".\"table_name\" = '%s';";
					// Grab a new query
					QSqlQuery *qsqDescription = this->newQuery();
					// Prepare the statement
					qsqDescription->prepare(this->queryf(strDescribeStatement.toLatin1().constData(), this->getDatabase(), strSchema, strTable));
					// We only want to traverse forward
					qsqDescription->setForwardOnly(true);
					// Try to execute the query
					if (!qsqDescription->exec()) {
						// We're done, return the empty description
						return mapDescription;
					}
					// Iterate over the results
					while (qsqDescription->next()) {
						// Create the column vector
						QVector<QString> vecColumn;
						// Set the field type into the vector
						vecColumn.append(qsqDescription->value("data_type").toString());
						// Append an empty value to the vector
						vecColumn.append(""); // TODO - Add actual size to the vector if it exists
						// Check for a primary key
						if (qsqDescription->value("column_key").toString().toLower() == "pri") {
							// Append the extra column data value to the vector
							vecColumn.append("PRI");
						}
						// Set the column into the description
						mapDescription.insert(qsqDescription->value("column_name").toString(), vecColumn);
					}
					// We're done with the query
					qsqDescription->finish();
					// We're done, the description has been loaded
					return mapDescription;
				}

				QString Pg::escapeColumn(QString strColumn) {
					// Return the quoted column
					return QString("\"%1\"").arg(strColumn);
				}

				QString Pg::escapeTable(QString strTable) {
					// Return the quoted schema and table name
					return QString("\"%1\"").arg(strTable);
				}

				QString Pg::escapeValue(QVariant varValue) {
					// Determine the type
					if (static_cast<enum QMetaType::Type>(varValue.type()) == QMetaType::Int) {                  // Integer
						// We're done, return the string
						return QString::number(varValue.toInt());
					} else if (static_cast<enum QMetaType::Type>(varValue.type()) == QMetaType::Double) {        // Double Point
						// We're done, return the string
						return QString::number(varValue.toDouble());
					} else if (static_cast<enum QMetaType::Type>(varValue.type()) == QMetaType::Float) {         // Floating Point
						// We're done, return the string
						return QString::number(varValue.toFloat());
					} else if (static_cast<enum QMetaType::Type>(varValue.type()) == QMetaType::Bool) {          // Boolean
						// We're done, return the string
						return QString(varValue.toBool() ? "true" : "false");
					} else if (static_cast<enum QMetaType::Type>(varValue.type()) == QMetaType::QJsonArray) {    // JSON Array
						// We're done, return the string
						return QString::fromLatin1(QJsonDocument(varValue.toJsonArray()).toJson());
					} else if (static_cast<enum QMetaType::Type>(varValue.type()) == QMetaType::QJsonDocument) { // JSON Document
						// We're done, return the string
						return QString::fromLatin1(varValue.toJsonDocument().toJson());
					} else if (static_cast<enum QMetaType::Type>(varValue.type()) == QMetaType::QJsonObject) {   // JSON Object
						// We're done, return the string
						return QString::fromLatin1(QJsonDocument(varValue.toJsonObject()).toJson());
					} else if (varValue.isNull()) {                                                              // NULL Value
						// We're done, return the string
						return QString("NULL");
					} else {                                                                                     // Strings and Everything Else
						// We're done, return the string
						return QString("%1").arg(varValue.toString().replace("'", "''"));
					}
				}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			} /// End Crux::Provider::Sql::Dialect Namespace /////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} /// End Crux::Provider::Sql Namespace //////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	} /// End Crux::Provider Namespace ///////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} /// End Crux Namespace /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
