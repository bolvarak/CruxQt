///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CRUX_FLUENT_SQL_COLLECTION_HPP
#define CRUX_FLUENT_SQL_COLLECTION_HPP

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../../Provider/Sql/Engine.hpp"

// Check for the model class definition
#ifndef CRUX_FLUENT_SQL_MODEL_HPP
#include "Model.hpp"
#endif

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
	/// Crux::Sql Namespace //////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	namespace Fluent
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Crux::Fluent::Sql Namespace //////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////

		namespace Sql
		{

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Crux::Fluent::Sql::Collection Class Definition ///////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			class Collection : public QObject
			{

				///////////////////////////////////////////////////////////////////////////////////////////////////////
				/// Qt Object Recognition ////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////

				Q_OBJECT

				///////////////////////////////////////////////////////////////////////////////////////////////////////
				/// Protected Methods & Properties ///////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////

				protected:

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Properties ///////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This property contains the name of the connection from the connection pool to use
					 * @access protected
					 * @name Crux::Fluent::Sql::Collection::mConnectionName
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QString
					 */
					QString mConnectionName;

					/**
					 * @paragraph This property contains the last error that occurred in the instance
					 * @access protected
					 * @name Crux::Fluent::Sql::Collection::mError
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QString
					 */
					QString mError;

					/**
					 * paragraph This property contains the GROUP BY clause
					 * @access protected
					 * @name Crux::Fluent::Sql::Collection::mGroupBy
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QString
					 */
					QString mGroupBy;

					/**
					 * @paragraph This property explicitly defines the empty state of the collection
					 * @access protected
					 * @name Crux::Fluent::Sql::Collection::mIsEmpty
					 * @namespace Crux::Fluent::Sql
					 * @var bool
					 */
					bool mIsEmpty;

					/**
					 * @paragraph This property contains the record limit for the collection
					 * @access protected
					 * @name Crux::Fluent::Sql::Collection::mLimit
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QString
					 */
					QString mLimit;

					/**
					 * @paragraph This property contains the ORDER BY clause
					 * @access protected
					 * @name Crux::Fluent::Sql::Collection::mOrderBy
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QString
					 */
					QString mOrderBy;

					/**
					 * @paragraph This property defines whether or not the instance has been populated
					 * @access protected
					 * @name Crux::Fluent::Sql::Collection::mPopulated
					 * @namespace Crux::Fluent::Sql
					 * @var bool
					 */
					bool mPopulated;

					/**
					 * @paragraph This property contains the records for the collection
					 * @access protected
					 * @name Crux::Fluent::Sql::Collection::mRecords
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QList<Crux::Fluent::Sql::Model*>
					 */
					QList<Model *> mRecords;

					/**
					 * @paragraph This property contains the schema the table belongs to
					 * @access protected
					 * @name Crux::Fluent::Sql::Collection::mSchema
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QString
					 */
					QString mSchema;

					/**
					 * @paragraph This property contains the table to query initially
					 * @access protected
					 * @name Crux::Fluent::Collection::mTable
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QString
					 */
					QString mTable;

					/**
					 * @paragraph This property contains the extra WHERE clauses
					 * @access protected
					 * @name Crux::Fluent::Sql::Collection::mWhere
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QString
					 */
					QString mWhere;

				///////////////////////////////////////////////////////////////////////////////////////////////////////
				/// Methods //////////////////////////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////




				///////////////////////////////////////////////////////////////////////////////////////////////////////
				/// Public Methods & Properties //////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////

				public:

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Constructor //////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This method instantiates a new Collection object
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::Collection()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QObject* qoParent [0]
					 * @return Crux::Fluent::Sql::Sql::Collection*
					 */
					Collection(QObject *qoParent = 0);

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Methods //////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This method adds a one-to-many relationship to each record
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::eachHasMany()
					 * @namespace Crux::Fluent::Sql
					 * @param Crux::Fluent::Sql::Model* modContainer
					 * @param QtCore/QString strSourceColumn [QtCore/QString::null]
					 * @param QtCore/QString strTargetColumn [QtCore/QString::null]
					 * @return Crux::Fluent::Sql::Collection* this
					 */
					Collection *eachHasMany(Model *modContainer, QString strSourceColumn = QString::null, QString strTargetColumn = QString::null);

					/**
					 * @paragraph This method adds a one-to-one relationship to each record
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::eachHasOne()
					 * @namespace Crux::Fluent::Sql
					 * @param Crux::Fluent::Sql::Model* modContainer
					 * @param QtCore/QString strSourceColumn [QtCore/QString::null]
					 * @param QtCore/QString strTargetColumn [QtCore/QString::null]
					 * @return Crux::Fluent::Sql::Collection* this
					 */
					Collection *eachHasOne(Model *modContainer, QString strSourceColumn = QString::null, QString strTargetColumn = QString::null);

					/**
					 * @paragraph This method formats and adds a GROUP BY clause to the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::groupBy()
					 * @namespace Crux::Fluent::Sql
					 * @param const char* chrStatement
					 * @param QVariant ...
					 * @return Crux::Fluent::Sql::Collection* this
					 */
					Collection *groupBy(const char *chrStatement, ...);

					/**
					 * @paragraph This method returns the error state of the collection
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::hasError()
					 * @namespace Crux::Fluent::Sql
					 * @return bool
					 */
					bool hasError();

					/**
					 * @paragraph This method returns the empty state of the collection
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::isEmpty()
					 * @return bool
					 */
					bool isEmpty();

					/**
					 * @paragraph This method adds a LIMIT clause to the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::limit()
					 * @namespace Crux::Fluent::Sql
					 * @param int intCount
					 * @param int intOffset [0]
					 * @return Crux::Fluent::Sql::Collection* this
					 */
					Collection *limit(int intCount, int intOffset = 0);

					/**
					 * @paragraph This method adds an ORDER BY clause to the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::orderBy()
					 * @namespace Crux::Fluent::Sql
					 * @param const char* chrClause
					 * @param QVariant ...
					 * @return Crux::Fluent::Sql::Collection* this
					 */
					Collection *orderBy(const char *chrClause, ...);

					/**
					 * @paragraph This method populates the collection from the database
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::populate<TCollectionContainer>()
					 * @namespace Crux::Fluent::Sql
					 * @param Crux::Fluent::Sql::Model* modContainer
					 * @return Crux::Fluent::Sql::Collection* this
					 */
					Collection *populate(Model *modContainer);

					/**
					 * @paragraph This method adds a WHERE clause to the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::where()
					 * @namespace Crux::Fluent::Sql
					 * @param const char* chrClause
					 * @return Crux::Fluent::Sql::Collection* this
					 */
					Collection *where(const char *chrClause, ...);

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Converters ///////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This method converts the collection to JSON
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::toJson()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QJsonDocument
					 */
					QJsonDocument toJson();

					/**
					 * @paragraph This method converts the collection to a list
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::toList()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QVariantList
					 */
					QVariantList toList();

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Getters //////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This method returns the actual connection object from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::getConnection()
					 * @namespace Crux::Fluent::Sql
					 * @return Crux::Provider::Sql::Engine* Crux::Provider::Sql::Engine::getConnection(Crux::Fluent::Sql::Collection::mConnectionName)
					 */
					Engine *getConnection();

					/**
					 * @paragraph This method returns the connection name from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::getConnectionName()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QString Crux::Fluent::Sql::Collection::mConnectionName
					 */
					QString getConnectionName();

					/**
					 * @paragraph This method returns the error from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::getError()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QString Crux::Fluent::Sql::Collection::mError
					 */
					QString getError();

					/**
					 * @paragraph This method returns the GROUP BY clause from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::getGroupBy()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QString Crux::Fluent::Sql::Collection::mGroupBy
					 */
					QString getGroupBy();

					/**
					 * @paragraph This method returns the ORDER BY clause from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::getOrderBy()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QString Crux::Fluent::Sql::Collection::mOrderBy
					 */
					QString getOrderBy();

					/**
					 * @paragraph This method returns the LIMIT clause from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::getLimit()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QString Crux::Fluent::Sql::Collection::mLimit
					 */
					QString getLimit();

					/**
					 * @paragraph This method returns a single record from the instance from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::getRecord()
					 * @namespace Crux::Fluent::Sql
					 * @param int intIndex
					 * @return Crux::Fluent::Sql::Model* Crux::Fluent::Sql::Collection::mRecords.at(intIndex)
					 */
					Model *getRecord(int intIndex = 0);

					/**
					 * @paragraph This method returns the records list from the instance from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::getRecords()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QList<Crux::Fluent::Sql::Model*> Crux::Fluent::Sql::Collection::mRecords
					 */
					QList<Model *> getRecords();

					/**
					 * @paragraph This method returns the table's schema from the instance
					 * @access public
					 * @name Crux::Fluent::Collection::getSchema()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QString Crux::Fluent::Sql::Collection::mSchema
					 */
					QString getSchema();

					/**
					 * @paragraph This method returns the table name from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::getTable()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QString Crux::Fluent::Sql::Collection::mTable
					 */
					QString getTable();

					/**
					 * @paragraph This method returns the WHERE clause from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::getWhere()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QString Crux::Fluent::Sql::Collection::mWhere
					 */
					QString getWhere();

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Setters //////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This method sets the connection name from the connection pool into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::setConnectionName()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strName
					 * @return Crux::Fluent::Sql::Collection* this
					 */
					Collection *setConnectionName(QString strName);

					/**
					 * @paragraph This method set the error into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::setError()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strError
					 * @return Crux::Fluent::Sql::Collection* this
					 */
					Collection *setError(QString strError);

					/**
					 * @paragraph This method sets the GROUP BY into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::setGroupBy()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strClause
					 * @return Crux::Fluent::Sql::Collection* this
					 */
					Collection *setGroupBy(QString strClause);

					/**
					 * @paragraph This method sets the LIMIT clause into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::setLimit()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strClause
					 * @return Crux::Fluent::Sql::Collection* this
					 */
					Collection *setLimit(QString strClause);

					/**
					 * @paragraph This method sets the ORDER BY into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::setOrderBy()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strClause
					 * @return Crux::Fluent::Sql::Collection* this
					 */
					Collection *setOrderBy(QString strClause);

					/**
					 * @paragraph This method resets a single record into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::setRecord()
					 * @namespace Crux::Fluent::Sql
					 * @param int intIndex
					 * @param Crux::Fluent::Sql::Model* modRecord
					 * @return Crux::Fluent::Sql::Collection* this
					 */
					Collection *setRecord(int intIndex, Model *modRecord);

					/**
					 * @paragraph This method sets the record list into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::setRecords()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QList<Crux::Fluent::Sql::Model*> lstRecords
					 * @return Crux::Fluent::Sql::Collection* this
					 */
					Collection *setRecords(QList<Model *> lstRecords);

					/**
					 * @paragraph This method sets the table's schema into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::setSchema()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strSchema
					 * @return Crux::Fluent::Sql::Collection* this
					 */
					Collection *setSchema(QString strSchema);

					/**
					 * @paragraph This method sets the table name into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::setTable()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strTableName
					 * @return Crux::Fluent::Sql::Collection* this
					 */
					Collection *setTable(QString strTableName);

					/**
					 * @paragraph This method sets the WHERE clause into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Collection::setWhere()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strClause
					 * @return Crux::Fluent::Sql::Collection* this
					 */
					Collection *setWhere(QString strClause);

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			}; /// End Crux::Fluent::Sql::Collection Class Definition ////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		} /// End Crux::Fluent::Sql Namespace ////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	} /// End Crux::Fluent Namespace /////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} /// End Crux Namespace /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif /// End Definitions ///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
