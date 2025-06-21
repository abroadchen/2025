package mongoserver

import (
	"context"
	"fmt"
	"go.mongodb.org/mongo-driver/bson/primitive"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
	"go.mongodb.org/mongo-driver/mongo/readpref"
	"os"
	"time"
)

type Howie struct {
	Howie primitive.ObjectID `bson:"_id"`
	Email string
}

func NewHowie(email string) *Howie {
	return &Howie{primitive.NewObjectID(), email}
}

type MongoDB struct {
	client       *mongo.Client
	databasename string
	col          *mongo.Collection
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

func NewMongoDB(url string, database string, colname string) *MongoDB {
	mymongo := new(MongoDB)
	mymongo.databasename = database
	var err error
	if mymongo.client, err = mongo.Connect(GetContext(), options.Client().ApplyURI(url)); err != nil {
		CheckError(err)
	}
	fmt.Println("Connected to MongoDB!")
	if err = mymongo.client.Ping(GetContext(), readpref.Primary()); err != nil {
		CheckError(err)
	}
	mymongo.col = mymongo.client.Database(database).Collection(colname)
	return mymongo
}

func (mgdb *MongoDB) InsertData(mail string) {
	howdata := NewHowie(mail)
	_, err := mgdb.col.InsertOne(GetContext(), howdata)
	if err != nil {
		CheckError(err)
	}
}

func (mgdb *MongoDB) InsertMoreData(mails []string) {
	var myarr []interface{}
	for _, mail := range mails {
		myarr = append(myarr, *NewHowie(mail))
	}
	_, err := mgdb.col.InsertMany(GetContext(), myarr)
	if err != nil {
		CheckError(err)
	}
}
