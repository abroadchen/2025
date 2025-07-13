package mongo

import (
	"github.com/astaxie/beego/session/mysql"
	"gopkg.in/mgo.v2"
	"gopkg.in/mgo.v2/bson"
)

type MongoDBClient struct {
	mysession      *mgo.Session
	databasename   string
	collectionname string
	mongourl       string
	coltable       *mgo.Collection
}

func NewMongoDBClient(mongourl string, databasename string, collectionname string) *MongoDBClient {
	mongo := new(MongoDBClient)
	mongo.databasename = databasename
	mongo.collectionname = collectionname
	mongo.mongourl = mongourl
	var err error
	mongo.mysession, err = mgo.Dial(mongourl)
	if err != nil {
		panic(err)
	}
	mongo.mysession.SetMode(mgo.Monotonic, true)
	mongo.coltable = mongo.mysession.DB(mongo.databasename).C(mongo.collectionname)
	return mongo
}

func (MongoDBc *MongoDBClient) SaveLog(datalog DataLog) error {
	var err error
	err = MongoDBc.coltable.Insert(&datalog)
	if err != nil {
		return err
	} else {
		return nil
	}
}

func (MongoDBc *MongoDBClient) SaveLogs(datalogs []DataLog) error {
	for i := 0; i < len(datalogs); i++ {
		err := MongoDBc.SaveLog(datalogs[i])
		if err != nil {
			return err
		}
	}
	return nil
}

func (MongoDBc *MongoDBClient) GetAll() []DataLog {
	result := []DataLog{}
	err := MongoDBc.coltable.Find(nil).All(&result)
	if err != nil {
		return nil
	}
	return result
}

func (MongoDBc *MongoDBClient) FindLogByIP(IP string) []DataLog {
	result := []DataLog{}
	err := MongoDBc.coltable.Find(bson.M{"ip": IP}).All(&result)
	if err != nil {
		return nil
	}
	return result
}

func (MongoDBc *MongoDBClient) FindLogBySQL(sqlstr interface{}) []DataLog {
	result := []DataLog{}
	err := MongoDBc.coltable.Find(sqlstr.(map[string]interface{})).All(&result)
	if err != nil {
		return nil
	}
	return result
}

func (MongoDBc *MongoDBClient) FindLogByContent(info string) []DataLog {
	result := []DataLog{}
	//err := MongoDBc.coltable.Find(bson.M{"content": info}).All(&result)
	conditions := bson.M{"content": bson.RegEx{info, ""}}
	err := MongoDBc.coltable.Find(conditions).All(&result)

	if err != nil {
		return nil
	}
	return result
}
