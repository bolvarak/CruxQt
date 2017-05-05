///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CRUX_FLUENT_SQL_MODEL_HPP
#define CRUX_FLUENT_SQL_MODEL_HPP

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <QtCore/QDebug>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonParseError>
#include <QtCore/QJsonValue>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QVariantMap>
#include <QtCore/QVector>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include "../../Provider/Sql/Engine.hpp"

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

		namespace Sql
		{

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// Crux::Fluent::Sql::Model Class Definition ////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////

			class Model : public QObject
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
					 * @paragraph This property contains the column data for a record in the table
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::mColumns
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QVariantMap
					 */
					QVariantMap mColumns;

					/**
					 * @paragraph This property contains the name of the connection to use from the pool
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::mConnectionName
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QString
					 */
					QString mConnectionName;

					/**
					 * @paragraph This property contains the last error that occurred
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::mError
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QString
					 */
					QString mError;

					/**
					 * @paragraph This property contains a flag that denotes the empty state of the model
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::mIsEmpty
					 * @namespace Crux::Fluent::Sql
					 * @var bool
					 */
					bool mIsEmpty;

					/**
					 * @paragraph This property contains the one-to-many relationships for the model
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::mOneToMany
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QMap<QtCore/QString, QtCore/QVector<Crux::Fluent::Sql::Model*>>
					 */
					QMap<QString, QVector<Model *>> mOneToMany;

					/**
					 * @paragraph This property contains the one-to-one relationships
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::mOneToOne
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QMap<QtCore/QString, Crux::Fluent::Sql::Model*>
					 */
					QMap<QString, Model *> mOneToOne;

					/**
					 * @paragraph This property contains the column name of the table's primary key
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::mPrimaryKey
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QString
					 */
					QString mPrimaryKey;

					/**
					 * @paragraph This property contains the schema name for the model
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::mSchema
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QString
					 */
					QString mSchema;

					/**
					 * @paragraph This property contains the table name that the model should query
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::mTable
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QString
					 */
					QString mTable;

					/**
					 * @paragraph This property contains the table's meta data
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::mTableDescription
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QMap<QtCore/QString, QtCore/QVector<QtCore/QString>>
					 */
					QMap<QString, QVector<QString>> mTableDescription;

					/**
					 * @paragraph This property contains a extra WHERE clauses
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::mWhere
					 * @namespace Crux::Fluent::Sql
					 * @var QtCore/QString
					 */
					QString mWhere;

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Methods //////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This method provides the connection's open state, it can be overloaded
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::connectionIsOpen()
					 * @namespace Crux::Fluent::Sql
					 * @return bool
					 */
					virtual bool connectionIsOpen();

					/**
					 * @paragraph This method provides a DELETE statement based on the engine and data in the model, it can be overloaded
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::deleteStatement()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QString
					 */
					virtual QString deleteStatement();

					/**
					 * @paragraph This method searches the column data for a specified column name, it can be overloaded
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::findColumn()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strColumn
					 * @return QtCore/QString
					 */
					virtual QString findColumn(QString strColumn);

					/**
					 * @paragraph This method provides an INSERT statement based on the engine and data in the model, it can be overloaded
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::insertStatement()
					 * @namespace Crux::Fluent::Sql
					 * @param bool blnIncludePrimaryKey [false]
					 * @return QtCore/QString
					 */
					virtual QString insertStatement(bool blnIncludePrimaryKey = false);

					/**
					 * @paragraph This method determines whether or not the table's primary key is populated in the column data, it can be overloaded
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::primaryKeyExists()
					 * @namespace Crux::Fluent::Sql
					 * @return bool
					 */
					virtual bool primaryKeyExists();

					/**
					 * @paragraph This method is meant to be overloaded to provide a SELECT statement based on the engine and data in the model
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::selectStatement()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strColumn
					 * @param QtCore/QVariant [NULL]
					 * @return QtCore/QString
					 */
					virtual QString selectStatement(QString strColumn, QVariant varValue);

					/**
					 * @paragraph This method is meant to be overloaded to provide the meta data for the table based on the engine
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::tableDescription()
					 * @namespace Crux::Fluent::Sql
					 * @param bool blnCloseConnectionWhenDone [false]
					 * @return QtCore/QString
					 */
					virtual bool tableDescription(bool blnCloseConnectionWhenDone = false);

					/**
					 * @paragraph This method provides an UPDATE statement based on the engine and data in the model, it can be overloaded
					 * @access protected
					 * @name Crux::Fluent::Sql::Model::updateStatement()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QString
					 */
					virtual QString updateStatement();


				///////////////////////////////////////////////////////////////////////////////////////////////////////
				//// Public Methods & Properties /////////////////////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////

				public:

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Constructor //////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This method instantiates a new Fluent SQL Model
					 * @access public
					 * @name Crux::Fluent::Sql::Model::Model()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strConnectionName
					 * @param QtCore/QString strTable
					 * @param QtCore/QString strPrimaryKey [QtCore/QString::null]
					 * @param QtCore/QString strSchema [QtCore/QString::null]
					 * @param QtCore/QObject* qoParent [0]
					 * @return Crux::Fluent::Sql::Model*
					 */
					Model(QString strConnectionName, QString strTable, QString strPrimaryKey = QString::null, QString strSchema = QString::null, QObject *qoParent = 0);

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Methods //////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This method determines whether or not an error has occurred in the model
					 * @access public
					 * @name Crux::Fluent::Sql::Model::hasError()
					 * @namespace Crux::Fluent::Sql
					 * @return bool
					 */
					bool hasError();

					/**
					 * @paragraph This method attaches a one-to-many collection to the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::hasMany()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strName
					 * @param Crux::Fluent::Sql::Model* modContainer
					 * @param QtCore/QString strSourceColumn [QtCore/QString::null]
					 * @param QtCore/QString strTargetColumn [QtCore/QString::null]
					 * @return Crux::Fluent::Sql::Model* this
					 */
					Model *hasMany(Model *modContainer, QString strSourceColumn = QString::null, QString strTargetColumn = QString::null);

					/**
					 * @paragraph This method attaches a one-to-one model to the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::hasOne()
					 * @namespace Crux::Fluent::Sql
					 * @param Crux::Fluent::Sql::Model* modContainer
					 * @param QtCore/QString strSourceColumn [QtCore/QString::null]
					 * @param QtCore/QString strTargetColumn [QtCore/QString::null]
					 * @return Crux::Fluent::Sql::Model* this
					 */
					Model *hasOne(Model *modContainer, QString strSourceColumn = QString::null, QString strTargetColumn = QString::null);

					/**
					 * @paragraph This method determines whether or not the model is empty, it can be overloaded
					 * @access public
					 * @name Crux::Fluent::Sql::Model::isEmpty()
					 * @namespace Crux::Fluent::Sql
					 * @return bool
					 */
					virtual bool isEmpty();

					/**
					 * @paragraph This method loads a record from the database into the model instance, it can be overloaded
					 * @access public
					 * @name Crux::Fluent::Sql::Model::load()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QVariant varUniqueIdentifier
					 * @param QtCore/QString strColumn [QtCore/QString::null]
					 * @return Crux::Fluent::Sql::Model* this
					 */
					virtual Model *load(QVariant varUniqueIdentifier, QString strColumn = QString::null);

					/**
					 * @paragraph This method deletes the record in the model from the database table, it can be overloaded
					 * @access public
					 * @name Crux::Fluent::Sql::Model::purge()
					 * @namespace Crux::Fluent::Sql
					 * @return Crux::Fluent::Sql::Model* this
					 */
					virtual Model *purge();

					/**
					 * @paragraph This method undoes the purge action from the model, it can be overloaded
					 * @access public
					 * @name Crux::Fluent::Sql::Model::recover()
					 * @namespace Crux::Fluent::Sql
					 * @return Crux::Fluent::Sql::Model* this
					 */
					virtual Model *recover();

					/**
					 * @paragraph This method saves the data in the model to a record in the table, it can be overloaded
					 * @access public
					 * @name Crux::Fluent::Sql::Model::save()
					 * @namespace Crux::Fluent::Sql
					 * @return Crux::Fluent::Sql::Model* this
					 */
					virtual Model *save(bool blnForceInsert = false);

					/**
					 * @paragraph This method formats and adds the WHERE clause to the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::where()
					 * @namespace Crux::Fluent::Sql
					 * @param const char* chrClauses
					 * @param QVariant...
					 * @return Crux::Fluent::Sql::Model* this
					 */
					virtual Model *where(const char *chrClauses, ...);

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Converters ///////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This method converts the model instance to a JSON document object, it can be overloaded
					 * @access public
					 * @name Crux::Fluent::Sql::Model::toJson()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QJsonDocument
					 */
					virtual QJsonDocument toJson();

					/**
					 * @paragraph This method converts the model instance to a variant map, it can be overloaded
					 * @access public
					 * @name Crux::Fluent::Sql::Model::toMap()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QVariantMap
					 */
					virtual QVariantMap toMap();

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Getters //////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This method returns a column's value from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::get()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strColumn
					 * @param QtCore/QVariant varDefault [QVariant()]
					 * @return QtCore/QVariant
					 */
					QVariant get(QString strColumn, QVariant varDefault = QVariant());

					/**
					 * @paragraph This method returns a column's value from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::getColumn()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strColumn
					 * @param QtCore/QVariant varDefault [QVariant()]
					 * @return QtCore/QVariant
					 */
					QVariant getColumn(QString strColumn, QVariant varDefault = QVariant());

					/**
					 * @paragraph This method returns the column data map from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::getColumns()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QVariantMap
					 */
					QVariantMap getColumns();

					/**
					 * @paragraph This method returns the database connection from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::getConnection()
					 * @namespace Crux::Fluent::Sql
					 * @return Crux::Provider::Engine*
					 */
					Engine *getConnection();

					/**
					 * @paragraph This method returns the connection pool instance name from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::getConnectionName()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QString
					 */
					QString getConnectionName();

					/**
					 * @paragraph This method returns the last error that occurred in the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::getError()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QString
					 */
					QString getError();

					/**
					 * @paragraph This method returns the table's primary key column name from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::getPrimaryKey()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QString
					 */
					QString getPrimaryKey();

					/**
					 * @paragraph This method returns the schema name from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::getSchema()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QString
					 */
					QString getSchema();

					/**
					 * @paragraph This method returns the table name from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::getTable()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QString
					 */
					QString getTable();

					/**
					 * @paragraph This method returns the table's description from the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::getTableDescription()
					 * @namespace Crux::Fluent::Sql
					 * @return QtCore/QMap<QtCore/QString, QtCore/QVector<QtCore/QString>>
					 */
					QMap<QString, QVector<QString>> getTableDescription();

					///////////////////////////////////////////////////////////////////////////////////////////////////
					/// Setters //////////////////////////////////////////////////////////////////////////////////////
					/////////////////////////////////////////////////////////////////////////////////////////////////

					/**
					 * @paragraph This method sets a column's value into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::set()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strColumn
					 * @param QtCore/QVariant varValue
					 * @return Crux::Fluent::Sql::Model* this
					 */
					Model *set(QString strColumn, QVariant varValue);

					/**
					 * @paragraph This method sets a column's value into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::setColumn()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strColumn
					 * @param QtCore/QVariant varValue
					 * @return Crux::Fluent::Sql::Model* this
					 */
					Model *setColumn(QString strColumn, QVariant varValue);

					/**
					 * @paragraph This method sets the column data map into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::setColumns()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QVariantMap mapColumns
					 * @return Crux::Fluent::Sql::Model* this
					 */
					Model *setColumns(QVariantMap mapColumns);

					/**
					 * @paragraph This method sets the connection into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::setConnection()
					 * @namespace Crux::Fluent::Sql
					 * @param Crux::Provider::Entine* dbConnection
					 * @return Crux::Fluent::Sql::Model* this
					 */
					Model *setConnection(Engine *dbConnection);

					/**
					 * @paragraph This method sets the connection name into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::setConnectionName()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strName
					 * @return Crux::Fluent::Sql::Model* this
					 */
					Model *setConnectionName(QString strName);

					/**
					 * @paragraph This method sets the error message into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::setError()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strMessage
					 * @return Crux::Fluent::Sql::Model* this
					 */
					Model *setError(QString strMessage);

					/**
					 * @paragraph This method sets the table's primary key column name into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::setPrimaryKey()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strColumn
					 * @return Crux::Fluent::Sql::Model* this
					 */
					Model *setPrimaryKey(QString strColumn);

					/**
					 * @paragraph This method sets the schema into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::setSchema()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strName
					 * @return Crux::Fluent::Sql::Model* this
					 */
					Model *setSchema(QString strName);

					/**
					 * @paragraph This method sets the table name into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::setTable()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strName
					 * @return Crux::Fluent::Sql::Model* this
					 */
					Model *setTable(QString strName);

					/**
					 * @paragraph This method sets the table meta data into the instance
					 * @access public
					 * @name Crux::Fluent::Sql::Model::setTableDescription()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QMap<QtCore/QString, QtCore/QVariant<QtCore/QString>> mapDescription
					 * @return Crux::Fluent::Sql::Model* this
					 */
					Model *setTableDescription(QMap<QString, QVector<QString>> mapDescription);

					/**
					 * @paragraph This method sets the WHERE clause(s) directly into the instance
					 * @access public
					 * @name Crux::Fluent::setWhereClause()
					 * @namespace Crux::Fluent::Sql
					 * @param QtCore/QString strClause
					 * @return Crux::Fluent::Sql::Model* this
					 */
					Model *setWhereClause(QString strClause);

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			}; /// End Crux::Fluent::Sql::Model Class Definition /////////////////////////////////////////////////////
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
