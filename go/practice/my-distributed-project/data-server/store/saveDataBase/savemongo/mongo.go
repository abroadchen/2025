package main

import (
	"context"
	"fmt"
	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/bson/primitive"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
	"go.mongodb.org/mongo-driver/mongo/readpref"
	"os"
	"time"
)

type Howie struct {
	Howie       primitive.ObjectID `bson:"_id"`
	Name        string             `bson:"name"`
	Pwd         string             `bson:"pwd"`
	Age         int64              `bson:"age"`
	CreateTime  int64              `bson:"createtime"`
	ExpiredTime time.Time          `bson:"expiredtime"`
}

func GetArray() (data []interface{}) {
	var i int64
	for i = 0; i < 10; i++ {
		data = append(data, Howie{
			primitive.NewObjectID(),
			fmt.Sprintf("how%d", i),
			fmt.Sprintf("pwd%d", i),
			i + 10,
			time.Now().Unix(),
			time.Now(),
		})
	}
	return data
}

func GetContext() (ctx context.Context) {
	ctx, _ = context.WithTimeout(context.Background(), 10*time.Second)
	return
}

func CheckError(err error) {
	if err != nil {
		if err == mongo.ErrNilDocument {
			fmt.Println("MongoDB collection does not exist")
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
	fmt.Println("Connected to MongoDB!")
	if err = client.Ping(GetContext(), readpref.Primary()); err != nil {
		CheckError(err)
	}
	collection := client.Database("test").Collection("Howie")
	collection.Drop(GetContext())
	howdata := GetArray()
	insertOneRes, err := collection.InsertOne(GetContext(), howdata[0])
	if err != nil {
		CheckError(err)
	}
	fmt.Println("insert one's id", insertOneRes.InsertedID)

	insertMoreRes, err := collection.InsertMany(GetContext(), howdata[1:])
	if err != nil {
		CheckError(err)
	}
	fmt.Println("insert one's id", insertMoreRes.InsertedIDs)
	var howie Howie
	if err := collection.FindOne(GetContext(), bson.D{{"name", "how2"}}).Decode(&howie); err != nil {
		CheckError(err)
	}
	fmt.Println("howie2 is ", howie)

}

func main() {
	TestMongo("mongodb://localhost:27017")
}
