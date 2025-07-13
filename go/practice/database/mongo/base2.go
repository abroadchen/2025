package mongo

import (
	"gopkg.in/mgo.v2"
	"time"
)

const mongourl = "mongodb://localhost:27017"

func ConnectMongo() (*mgo.Database, *mgo.Session) {
	session, err := mgo.Dial(mongourl)
	session.SetMode(mgo.Monotonic, true)
	db := session.DB("test")
	if err != nil {
		return nil, nil
	} else {
		return db, session
	}
}

func WriteDB() {
	data := &mgo.DialInfo{
		Addrs:   []string{"localhost:27017"},
		Direct:  false,
		Timeout: 60 * time.Second,
	}
}
