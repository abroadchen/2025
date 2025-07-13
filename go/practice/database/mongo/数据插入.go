package mongo

import (
	"fmt"
	"gopkg.in/mgo.v2"
	"gopkg.in/mgo.v2/bson"
)

type DoTags struct {
	DoTag  string `bson:"DoTag, omitempty"`
	Weight int    `bson:"Weight, minimize"`
}

type EmailTag struct {
	Email     string   `bson:"Email, omitempty"`
	Tags      []string `bson:"Tags, omitempty"`
	DoingTags []DoTags `bson:"DoTags, omitempty"`
}

func NewDoTags(DoingTag string, weight int) DoTags {
	d := DoTags{}
	d.DoTag = DoingTag
	d.Weight = weight
	return d
}

func NewEmailTag(Email string, Tags []string, DoingTags []string, weights []int) *EmailTag {
	e := new(EmailTag)
	e.Email = Email
	e.Tags = Tags
	for i := 0; i < len(DoingTags); i++ {
		e.DoingTags = append(e.DoingTags, NewDoTags(DoingTags[i], weights[i]))
	}
	return e
}

func main() {
	session, err := mgo.Dial("localhost:27017")
	if err != nil {
		panic(err)
	}
	defer session.Close()
	c := session.DB("DataAll").C("EmailTag1")
	c.Insert(NewEmailTag("", []string{}))
	dataall := []EmailTag{}
	err = c.Find(bson.M{}).All(&dataall)
	fmt.Println(len(dataall))
	for i := 0; i < len(dataall); i++ {
		fmt.Println(dataall[i])
	}
}
