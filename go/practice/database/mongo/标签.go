package mongo

import (
	"gopkg.in/mgo.v2"
	"gopkg.in/mgo.v2/bson"
	"log"
)

type PersonTag struct {
	QQ   string
	Tags []string
}

func main() {
	session, err := mgo.Dial(mongourl)
	session.SetMode(mgo.Monotonic, true)
	if err != nil {
		panic(err)
	}
	defer session.Close()

	c := session.DB("test").C("people")
	err = c.Insert(&PersonTag{})
	if err != nil {
		log.Fatal(err)
	}

	result := PersonTag{}
	err = c.Find(bson.M{"qq": "test"}).One(&result)
	if err != nil {
		log.Fatal(err)
	}
}
