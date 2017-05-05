///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Collection.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Imports //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using Crux::Provider::Sql::Engine;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Crux Namespace ///////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Crux
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Crux::Fluent Namespace ///////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace Fluent
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Crux::Fluent::Sql Namespace //////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////

		namespace Sql {


			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			Collection::Collection(QObject *qoParent) : QObject(qoParent) {
				// Set the connection name into the instance
				this->mConnectionName = QString::null;
				// Set the table schema into the instance
				this->mSchema = QString::null;
				// Set the table name into the instance
				this->mTable = QString::null;
				// Default the error
				this->mError = QString::null;
				// Default our clauses
				this->mGroupBy = QString::null;
				this->mLimit = QString::null;
				this->mOrderBy = QString::null;
				this->mWhere = QString::null;
				// Default the records
				this->mRecords = QList<Model *>();
				// Default the empty flag
				this->mIsEmpty = true;
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Protected Methods ////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////



			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Public Methods ///////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			Collection *Collection::groupBy(const char *chrClause, ...) {
				// Define our argument container
				va_list valArguments;
				// Unpack the arguments
				va_start(valArguments, chrClause);
				// Add the GROUP BY clause to the instance
				this->mGroupBy = this->getConnection()->formatQueryString(chrClause, valArguments);
				// We're done with the argument list
				va_end(valArguments);
				// We're done, return the instance
				return this;
			}

			Collection *Collection::eachHasMany(Model *modContainer, QString strSourceColumn, QString strTargetColumn) {
				// Check for population
				if (!this->mPopulated) {
					// We're done, return the instance
					return this;
				}
				// Iterate over each of the records
				for (Model *modRecord: this->mRecords) {
					// Populate the relationship
					modRecord->hasMany(modContainer, strSourceColumn, strTargetColumn);
				}
				// We're done, return the instance
				return this;
			}

			Collection *Collection::eachHasOne(Model *modContainer, QString strSourceColumn, QString strTargetColumn) {
				// Check for population
				if (!this->mPopulated) {
					// We're done, return the instance
					return this;
				}
				// Iterate over each of the records
				for (Model *modRecord: this->mRecords) {
					// Populate the relationship
					modRecord->hasOne(modContainer, strSourceColumn, strTargetColumn);
				}
				// We're done, return the instance
				return this;
			}

			bool Collection::hasError() {
				// Return the error state
				return (this->mError.isEmpty() || this->mError.isNull() || (this->mError == QString::null));
			}

			bool Collection::isEmpty() {
				// Return the empty state
				return (this->mRecords.isEmpty() || (this->mRecords.size() == 0) || this->mIsEmpty);
			}

			Collection *Collection::limit(int intCount, int intOffset) {
				// Check for an offset
				if (intOffset <= 0) {
					// Set the LIMIT clause into the instance
					this->mLimit = this->getConnection()->queryf("LIMIT %i", intCount);
				} else {
					// Set the LIMIT clause into the instance
					this->mLimit = this->getConnection()->queryf("LIMIT %i,%i", intCount, intOffset);
				}
				// We're done, return the instance
				return this;
			}

			Collection *Collection::orderBy(const char *chrClause, ...) {
				// Define our argument container
				va_list valArguments;
				// Unpack the argument
				va_start(valArguments, chrClause);
				// Add the ORDER BY clause to the instance
				this->mOrderBy = this->getConnection()->formatQueryString(chrClause, valArguments);
				// We're done with the argument list
				va_end(valArguments);
				// We're done, return the instance
				return this;
			}

			Collection *Collection::populate(Model *modContainer) {
				// Check for a connection name
				if (this->mConnectionName == QString::null) {
					// Set the connection name into the instance
					this->mConnectionName = modContainer->getConnectionName();
				}
				// Check for a schema
				if (this->mSchema == QString::null) {
					// Set the table schema into the instance
					this->mSchema = modContainer->getSchema();
				}
				// Check for a table
				if (this->mTable == QString::null) {
					// Set the table name into the instance
					this->mTable = modContainer->getTable();
				}
				// Reset the error
				this->mError = QString::null;
				// Clear the records
				this->mRecords.clear();
				// Define our statement placeholder
				QString strStatement;
				// Describe the table
				QMap<QString, QVector<QString>> mapDescription = this->getConnection()->describe(this->mTable,
																								 this->mSchema);
				// Check for a description
				if (mapDescription.isEmpty()) {
					// TODO - Emit Error Signal
					// Set the error
					this->mError = QString("Unable to load table description for table:  %1").arg(this->mTable);
					// Reset the empty flag
					this->mIsEmpty = true;
					// We're done, return the instance
					return this;
				}
				// Define our primary key placeholder
				QString strPrimaryKey;
				// Iterate over the description
				for (QString strColumn: mapDescription.keys()) {
					// Check the column
					if ((mapDescription.value(strColumn).size() >= 3) &&
						(mapDescription.value(strColumn).at(2).toLower() == "pri")) {
						// Reset the primary
						strPrimaryKey = strColumn;
					}
				}
				// Check for a schema
				if (this->mSchema == QString::null) {
					// Set the statement
					strStatement = this->getConnection()->queryf("SELECT %T.%C FROM %T", this->mTable, strPrimaryKey,
																 this->mTable);
				} else {
					// Set the statement
					strStatement = this->getConnection()->queryf("SELECT %T.%C FROM %T.%T", this->mTable, strPrimaryKey,
																 this->mSchema, this->mTable);
				}
				// Check for a GROUP BY clause
				if (this->mGroupBy != QString::null) {
					// Add the clause to the statement
					strStatement.append(this->mGroupBy.prepend(" "));
				}
				// Check for an ORDER BY clause
				if (this->mOrderBy != QString::null) {
					// Add the clause to the statement
					strStatement.append(this->mOrderBy.prepend(" "));
				}
				// Check for a LIMIT clause
				if (this->mLimit != QString::null) {
					// Add the clause to the statement
					strStatement.append(this->mLimit.prepend(" "));
				}
				// Create the query
				QSqlQuery *qsqCollection = this->getConnection()->newQuery();
				// We only want to traverse forward in the results
				qsqCollection->setForwardOnly(true);
				// Try to execute the query
				if (!qsqCollection->exec(strStatement)) {
					// TODO - Emit Error Signal
					// Reset the error into the instance
					this->mError = qsqCollection->lastError().text();
					// We're done, return the instance
					return this;
				}
				// Reserve the memory for the records
				this->mRecords.reserve(qsqCollection->size());
				// Iterate over the records
				while (qsqCollection->next()) {
					// Create our model
					Model *modRelationship = new Model(this->mConnectionName, this->mTable, strPrimaryKey,
															 this->mSchema);
					// Append the loaded container
					this->mRecords.append(modRelationship->load(qsqCollection->value(strPrimaryKey), strPrimaryKey));
				}
				// Check the record count
				if (!this->mRecords.isEmpty() && this->mRecords.size() > 0) {
					// Reset the empty flag
					this->mIsEmpty = false;
					// Reset the populated flag
					this->mPopulated = true;
				} else {
					// Reset the empty flag
					this->mIsEmpty = true;
					// Reset the populated flag
					this->mPopulated = false;
				}
				// We're done, return the instance
				return this;
			}

			Collection *Collection::where(const char *chrClause, ...) {
				// Define our argument container
				va_list valArguments;
				// Unpack the arguments
				va_start(valArguments, chrClause);
				// Add the WHERE clause to the instance
				this->mWhere = this->getConnection()->formatQueryString(chrClause, valArguments);
				// We're done with the argument list
				va_end(valArguments);
				// Check for the WHERE keyword
				if (this->mWhere.toLower().indexOf("where", 0) == -1) {
					// Prepend the WHERE keyword
					this->mWhere.prepend("WHERE ");
				}
				// We're done, return the instance
				return this;
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Converters ///////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			QJsonDocument Collection::toJson() {
				// Define our JSON array
				QJsonArray qjaCollection = QJsonArray::fromVariantList(this->toList());
				// Return our JSON document
				return QJsonDocument(qjaCollection);
			}

			QVariantList Collection::toList() {
				// Define our list container
				QVariantList qvlCollection;
				// Iterate over the records
				for (Model *modRecord: this->mRecords) {
					// Add the record to the list
					qvlCollection.append(modRecord->toMap());
				}
				// We're done, return the list
				return qvlCollection;
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Getters //////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			Engine *Collection::getConnection() {
				// Return the connection object
				return Engine::getConnection(this->mConnectionName);
			}

			QString Collection::getConnectionName() {
				// Return the connection name from the instance
				return this->mConnectionName;
			}

			QString Collection::getError() {
				// Return the error from the instance
				return this->mError;
			}

			QString Collection::getGroupBy() {
				// Return the GROUP BY clause from the instance
				return this->mGroupBy;
			}

			QString Collection::getOrderBy() {
				// Return the ORDER BY clause from the instance
				return this->mOrderBy;
			}

			QString Collection::getLimit() {
				// Return the LIMIT clause from the instance
				return this->mLimit;
			}

			Model *Collection::getRecord(int intIndex) {
				// Return the record from the instance
				return this->mRecords.at(intIndex);
			}

			QList<Model *> Collection::getRecords() {
				// Return the record list from the instance
				return this->mRecords;
			}

			QString Collection::getSchema() {
				// Return the table's schema from the instance
				return this->mSchema;
			}

			QString Collection::getTable() {
				// Return the table name from the instance
				return this->mTable;
			}

			QString Collection::getWhere() {
				// Return the WHERE clause from the instance
				return this->mWhere;
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Setters //////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			Collection *Collection::setConnectionName(QString strName) {
				// Set the connection pool name into the instance
				this->mConnectionName = strName;
				// We're done, return the instance
				return this;
			}

			Collection *Collection::setError(QString strError) {
				// Set the error into the instance
				this->mError = strError;
				// We're done, return the instance
				return this;
			}

			Collection *Collection::setGroupBy(QString strClause) {
				// Set the GROUP BY clause into the instance
				this->mGroupBy = strClause;
				// We're done, return the instance
				return this;
			}

			Collection *Collection::setLimit(QString strClause) {
				// Set the LIMIT clause into the instance
				this->mLimit = strClause;
				// We're done, return the instance
				return this;
			}

			Collection *Collection::setOrderBy(QString strClause) {
				// Set the ORDER BY clause into the instance
				this->mOrderBy = strClause;
				// We're done, return the instance
				return this;
			}

			Collection *Collection::setRecord(int intIndex, Model *modRecord) {
				// Set the record into the instance
				this->mRecords.insert(intIndex, modRecord);
				// We're done, return the instance
				return this;
			}

			Collection *Collection::setRecords(QList<Model *> lstRecords) {
				// Set the records into the instance
				this->mRecords = lstRecords;
				// We're done, return the instance
				return this;
			}

			Collection *Collection::setSchema(QString strSchema) {
				// Set the schema name into the instance
				this->mSchema = strSchema;
				// We're done, return the instance
				return this;
			}

			Collection *Collection::setTable(QString strTableName) {
				// Set the table name into the instance
				this->mTable = strTableName;
				// We're done, return the instance
				return this;
			}

			Collection *Collection::setWhere(QString strClause) {
				// Set the WHERE clause into the instance
				this->mWhere = strClause;
				// We're done, return the instance
				return this;
			}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} /// End Crux::Fluent::Sql Namespace ////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	} /// End Crux::Fluent Namespace /////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} /// End Crux Namespace /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
