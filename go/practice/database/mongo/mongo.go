package mongo

import (
	"context"
	"fmt"
	"go.mongodb.org/mongo-driver/bson/primitive"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
	"go.mongodb.org/mongo-driver/mongo/readpref"
	"gopkg.in/mgo.v2/bson"
	"os"
	"time"
)

type Howie struct {
	HowieID     primitive.ObjectID `bson:"_id"`
	Name        string
	Pwd         string
	Age         int64
	Created     int64
	ExpiredTime time.Time
}

func GetArray() (data []interface{}) {
	var i int64
	for i = 0; i < 10; i++ {
		data = append(data, Howie{
			HowieID:     primitive.NewObjectID(),
			Name:        fmt.Sprintf("Howie %d", i),
			Pwd:         fmt.Sprintf("Pwd%d", i),
			Age:         i + 10,
			Created:     time.Now().Unix(),
			ExpiredTime: time.Now(),
		})
	}
	return
}

func GetContext() (ctx context.Context) {
	ctx, _ = context.WithTimeout(context.Background(), 10*time.Second)
	return
}

func CheckError(err error) {
	if err != nil {
		if err == mongo.ErrNilDocument {
			fmt.Printf("没有找到数据")
			os.Exit(1)
		} else {
			fmt.Println(err)
			os.Exit(1)
		}
	}
}

func TestMongo(url string) {
	var (
		err    error
		client *mongo.Client
	)
	if client, err = mongo.Connect(GetContext(), options.Client().ApplyURI(url)); err != nil {
		CheckError(err)
	}
	if err = client.Ping(GetContext(), readpref.Primary()); err != nil {
		CheckError(err)
	}
	collection := client.Database("test").Collection("howie")
	collection.Drop(GetContext())
	howdata := GetArray()
	var insertOneRes *mongo.InsertOneResult
	if insertOneRes, err = collection.InsertOne(GetContext(), howdata[0]); err != nil {
		CheckError(err)
	}
	fmt.Printf("Inserted a single document: %+v\n", insertOneRes.InsertedID)

	var insertMoreRes *mongo.InsertManyResult
	if insertMoreRes, err = collection.InsertMany(GetContext(), howdata[1:]); err != nil {
		CheckError(err)
	}
	fmt.Printf("Inserted a single document: %+v\n", insertMoreRes.InsertedIDs)

	var howie Howie
	if err := collection.FindOne(GetContext(), bson.D{{"name": "how"}}).Decode(&howie); err != nil {
		CheckError(err)
	}
	fmt.Printf("Inserted a single document: %+v\n", howie)

}

func main() {
	TestMongo("mongodb://localhost:27017")
}
