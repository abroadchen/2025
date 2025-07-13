package mongo

import (
	"fmt"
	"gopkg.in/mgo.v2"
	"gopkg.in/mgo.v2/bson"
)

type MongoDB struct {
	DBurl          string
	DBname         string
	Collectionname string
	Session        *mgo.Session
	Collection     *mgo.Collection
}

func NewMongoDB(DBurl, DBname, Collectionname string) *MongoDB {
	mdb := new(MongoDB)
	mdb.DBurl = DBurl
	mdb.DBname = DBname
	mdb.Collectionname = Collectionname

	var err error
	mdb.Session, err = mgo.Dial(DBurl)
	if err != nil {
		fmt.Println(err)
	}
	mdb.Collection = mdb.Session.DB(DBname).C(Collectionname)
	return mdb
}

func (m *MongoDB) Findall() []EmailTag {
	dataall := []EmailTag{}
	err := m.Collection.Find(bson.M{}).All(&dataall)
	if err != nil {
		return nil
	} else {
		return dataall
	}
}

func (m *MongoDB) FindallLimit(limit int) []EmailTag {
	dataall := []EmailTag{}
	err := m.Collection.Find(bson.M{}).Limit(limit).All(&dataall)
	if err != nil {
		return nil
	} else {
		return dataall
	}
}

/*
page 每页有几个
i 第几页
*/
func (m *MongoDB) FindallmorePage(page, i int) []EmailTag {
	dataall := []EmailTag{}
	err := m.Collection.Find(bson.M{}).Skip(page * (i - 1)).Limit(page).All(&dataall)
	if err != nil {
		return nil
	} else {
		return dataall
	}
}

func (m *MongoDB) FindallByDoTagOR(Tags []string) []EmailTag {
	dataall := []EmailTag{}
	err := m.Collection.Find(bson.M{"DoTags.DoTag": bson.M{"in": Tags}}).All(&dataall)
	if err != nil {
		return nil
	} else {
		return dataall
	}
}

func (m *MongoDB) FindallByDoTagAND(Tags []string) []EmailTag {
	dataall := []EmailTag{}
	err := m.Collection.Find(bson.M{"DoTags.DoTag": bson.M{"all": Tags}}).All(&dataall)
	if err != nil {
		return nil
	} else {
		return dataall
	}
}

func Reverse(e []EmailTag) []EmailTag {
	for i, j := 0, len(e)-1; i < j; i, j = i+1, j-1 {
		e[i], e[j] = e[j], e[i]
	}
	return e
}

func (m *MongoDB) FindallByDoTag(Tags []string, isbigtosmall bool, isor bool) []EmailTag {
	dataall := []EmailTag{}
	var err error
	if isor {
		if isbigtosmall {
			err = m.Collection.Find(bson.M{"DoTags.DoTag": bson.M{"in": Tags}}).Sort("-DoTags.Weight").All(&dataall)
		} else {
			err = m.Collection.Find(bson.M{"DoTags.DoTag": bson.M{"in": Tags}}).Sort("-DoTags.Weight").All(&dataall)
			dataall = Reverse(dataall)
		}
	} else {
		if isbigtosmall {
			err = m.Collection.Find(bson.M{"DoTags.DoTag": bson.M{"all": Tags}}).Sort("-DoTags.Weight").All(&dataall)
		} else {
			err = m.Collection.Find(bson.M{"DoTags.DoTag": bson.M{"all": Tags}}).Sort("+DoTags.Weight").All(&dataall)
		}
	}
	if err != nil {
		return nil
	} else {
		return dataall
	}
}

func (m *MongoDB) FindallByTagWeight(weight int) []EmailTag {
	dataall := []EmailTag{}
	err := m.Collection.Find(bson.M{"DoTags.Weight": bson.M{"in": []int{weight}}}).All(&dataall)
	if err != nil {
		return nil
	} else {
		return dataall
	}
}

func (m *MongoDB) FindallByTagWeightBig(weight int) []EmailTag {
	dataall := []EmailTag{}
	err := m.Collection.Find(bson.M{"DoTags.Weight": bson.M{"$gt": weight}}).All(&dataall)
	if err != nil {
		return nil
	} else {
		return dataall
	}
}

func (m *MongoDB) FindallBySourceTag(Tags []string) []EmailTag {
	dataall := []EmailTag{}
	err := m.Collection.Find(bson.M{"Tags": bson.M{"$in": Tags}}).All(&dataall)
	if err != nil {
		return nil
	} else {
		return dataall
	}
}

func (m *MongoDB) FindallByAndTags(Tag []string) []EmailTag {
	dataall := []EmailTag{}
	err := m.Collection.Find(bson.M{"Tags": bson.M{"$all": Tag}}).All(&dataall)
	if err != nil {
		return nil
	} else {
		return dataall
	}
}

func (m *MongoDB) FindallByTagsOne(Tag []string) []EmailTag {
	dataall := []EmailTag{}
	err := m.Collection.Find(bson.M{"Tags": bson.M{"$elemMatch": Tag}}).All(&dataall)
	if err != nil {
		return nil
	} else {
		return dataall
	}
}

func (m *MongoDB) FindallByRegex(reg string) []EmailTag {
	dataall := []EmailTag{}
	err := m.Collection.Find(bson.M{"Tags": bson.M{"$regex": reg}}).All(&dataall)
	if err != nil {
		return nil
	} else {
		return dataall
	}
}

func (m *MongoDB) ShowDBInfo() {
	fmt.Println(m.DBurl, m.DBname, m.Collectionname)
}

func (m *MongoDB) Insert(Email string, Tags []string, dotags []string, weights []int) error {
	if m.IsIn(Email) {
		return nil
	} else {
		data1 := NewEmailTag(Email, Tags, dotags, weights)
		err := m.Collection.Insert(data1)
		return err
	}
}

func (m *MongoDB) DeleteSame(tag1, tag2 []string) []string {
	tag1 = append(tag1, tag2...)
	mymap := make(map[string]int)
	for i := 0; i < len(tag1); i++ {
		_, ok := mymap[tag1[i]]
		if !ok {
			mymap[tag1[i]] = 1
		}
	}
	lastres := []string{}
	for k, _ := range mymap {
		lastres = append(lastres, k)
	}
	return lastres
}

func (m *MongoDB) Update(Email string, Tags []string) error {
	dataall := []EmailTag{}
	m.Collection.Find(bson.M{"Email": Email}).All(&dataall)
	oldtags := dataall[0].Tags
	nowtags := m.DeleteSame(oldtags, Tags)
	err := m.Collection.Update(bson.M{"Email": Email}, bson.M{"$set": bson.M{"Tags": nowtags}})
	return err
}

func (m *MongoDB) UpdateAdd(Email string, Tags []string) error {
	dataall := []EmailTag{}
	m.Collection.Find(bson.M{"Email": Email}).All(&dataall)
	oldtags := dataall[0].Tags
	addarr := []string{}
	for i := 0; i < len(Tags); i++ {
		var isin bool = false
		for j := 0; j < len(oldtags); j++ {
			if oldtags[j] == Tags[i] {
				isin = true
				break
			}
		}
		if !isin {
			addarr = append(addarr, Tags[i])
		}
	}
	var err error
	for k := 0; k < len(addarr); k++ {
		err = m.Collection.Update(bson.M{"Email": Email}, bson.M{"$push": bson.M{"Tags": addarr[k]}})
	}
	return err
}

func (m *MongoDB) UpdatedoTagsAdd(Email string, Tags []string, weights []int) error {
	dataall := []EmailTag{}
	m.Collection.Find(bson.M{"Email": Email}).All(&dataall)
	oldtags := dataall[0].DoingTags
	oldtagsstring := []string{}
	for i := 0; i < len(oldtags); i++ {
		oldtagsstring = append(oldtagsstring, oldtags[i].DoTag)
	}

	addarr := []DoTags{}
	for i := 0; i < len(Tags); i++ {
		var isin bool = false
		for j := 0; j < len(oldtagsstring); j++ {
			if oldtagsstring[j] == Tags[i] {
				isin = true
				break
			}
		}
		if !isin {
			addarr = append(addarr, DoTags{Tags[i], weights[i]})
		}
	}
	var err error
	for k := 0; k < len(addarr); k++ {
		err = m.Collection.Update(bson.M{"Email": Email}, bson.M{"$push": bson.M{"DoTags": addarr[k]}})
	}
	return err
}

func (m *MongoDB) UpdatedoTagsSub(Email string, Tags []string, weights []int) error {
	dataall := []EmailTag{}
	m.Collection.Find(bson.M{"Email": Email}).All(&dataall)
	oldtags := dataall[0].DoingTags
	oldtagsstring := []string{}
	for i := 0; i < len(oldtags); i++ {
		oldtagsstring = append(oldtagsstring, oldtags[i].DoTag)
	}

	var err error
	var nowtags []DoTags
	for i := 0; i < len(oldtags); i++ {
		var isin bool = false
		for j := 0; j < len(Tags); j++ {
			if oldtagsstring[i] == Tags[j] {
				isin = true

				break
			}
		}
		if !isin {
			nowtags = append(nowtags, oldtags[i])
			isin = false
		}

	}
	err = m.Collection.Update(bson.M{"Email": Email}, bson.M{"$set": bson.M{"DoTags": nowtags}})
	return err
}

func (m *MongoDB) UpdatedoTagsWeight(Email string, dotag string, weight int) {
	dataall := []EmailTag{}
	m.Collection.Find(bson.M{"Email": Email, "DoTags.DoTag": bson.M{"$in": []string{dotag}}}).All(&dataall)
	if len(dataall) == 0 {
		return
	}
	var getvalue int
	for i := 0; i < len(dataall[0].DoingTags); i++ {
		if dataall[0].DoingTags[i].DoTag == dotag {
			getvalue = dataall[0].DoingTags[i].Weight
			lastvalue := getvalue + weight
			dataall[0].DoingTags[i].Weight = lastvalue
			m.Collection.Update(bson.M{"Email": Email, "DoTags.DoTag": bson.M{"$in": []string{dotag}}}, bson.M{"$inc": bson.M{"DoTags.Weight": lastvalue}})
		}
	}
	//err := m.Collection.Update(bson.M{"Email": Email}, bson.M{"$set": bson.M{"DoTags": dataall[0].DoingTags}})
}

func (m *MongoDB) UpdateSourceTagsSub(Email string, Tags []string) error {
	dataall := []EmailTag{}
	m.Collection.Find(bson.M{"Email": Email}).All(&dataall)
	oldtags := dataall[0].Tags
	var err error
	for i := 0; i < len(Tags); i++ {
		for j := 0; j < len(oldtags); j++ {
			if oldtags[j] == Tags[i] {
				err = m.Collection.Update(bson.M{"Email": Email}, bson.M{"$pull": bson.M{"Tags": Tags[i]}})
				break
			}
		}
	}
	return err
}

func (m *MongoDB) IsIn(Email string) bool {
	dataall := []EmailTag{}
	err := m.Collection.Find(bson.M{"Email": Email}).All(&dataall)
	fmt.Println(len(dataall), err)
	if err != nil {
		panic(err)
	} else {
		if len(dataall) >= 1 {
			return true
		} else {
			return false
		}
	}
}

func (m *MongoDB) Insert1(e EmailTag) error {
	if m.IsIn(e.Email) {
		return m.Update(e)
	} else {
		err := m.Collection.Insert(e)
		return err
	}
}

func (m *MongoDB) Update1(e EmailTag) error {
	dataall := []EmailTag{}
	m.Collection.Find(bson.M{"Email": e.Email}).One(&dataall)
	oldtags := dataall[0].Tags
	nowtags := m.DeleteSame(oldtags, e.Tags)
	err := m.Collection.Update(bson.M{"Email": e.Email}, bson.M{"$set": bson.M{"DoTags": nowtags}})
	return err
}
