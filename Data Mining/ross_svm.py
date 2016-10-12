import numpy as np
import pandas as pd
from sklearn import cross_validation
from sklearn.svm import SVR
#from sklearn.metrics import mean_squared_error

def load_data():
    tt = pd.read_csv("train.csv",parse_dates=["Date"])
    #return type:list
    return cross_validation.train_test_split(tt,test_size=0.33)

def load_training_data():
    tt = pd.read_csv("train.csv",parse_dates=["Date"]) #type:DataFrame
    return tt

def load_test_data():
    t1 = pd.read_csv("test.csv",parse_dates=["Date"]) #type:DataFrame
    return t1

def load_store_data():
    #typelist = {'CompetitionOpenSinceYear':np.int64,'CompetitionOpenSinceMonth':np.int64}
    st = pd.read_csv("store.csv")
    st = st.fillna(0)
    st.CompetitionDistance = st.CompetitionDistance.astype(int)
    st.CompetitionOpenSinceYear = st.CompetitionOpenSinceYear.astype(int)
    st.CompetitionOpenSinceMonth = st.CompetitionOpenSinceMonth.astype(int)
    st.Promo2SinceYear = st.Promo2SinceYear.astype(int)
    st.Promo2SinceWeek = st.Promo2SinceWeek.astype(int)
    #print st.dtypes
    return st

def training_data_preprocessing(tt,st):
    tt["Year"] = tt.Date.dt.year
    tt["Month"] = tt.Date.dt.month #<type 'numpy.int64'>
    tt["Day"] = tt.Date.dt.day
    tt["WeekOfYear"] = tt.Date.dt.weekofyear
    #remove open == 0
    tt = tt[tt.Open!=0]
    #remove sales == 0
    tt = tt[tt.Sales!=0]
    tt["LogSales"] = np.log1p(tt["Sales"])
    #change values of stateholiday
    #tt = tt.StateHoliday.replace(['0','a','b','c'],[0,1,2,3])
    tt = pd.merge(tt, st, on='Store')
    rec = [0] * len(tt.index)
    for index, row in tt.iterrows():
        if (row["CompetitionOpenSinceYear"]==0) or ((row["Year"] - row["CompetitionOpenSinceYear"])>0):
            rec[index] = 1
        elif row["Year"] - row["CompetitionOpenSinceYear"]== 0:
            if row["Month"] - row["CompetitionOpenSinceMonth"] >= 0:
                rec[index] = 1
        else:
            pass
    tt["CompetitionOpen"] = rec

    rec = [0] * len(tt.index)
    for index, row in tt.iterrows():
        if (row["Promo2"]== 1) and (row["Year"] - row["Promo2SinceYear"] > 0):
            rec[index] = 1
        elif (row["Promo2"]==1) and (row["Year"] - row["Promo2SinceYear"] == 0):
            if row["WeekOfYear"] - row["Promo2SinceWeek"] >=0:
                rec[index] = 1
        else:
            pass
    tt["Promo2Open"] = rec

    rec = [4] * len(tt.index)
    m = {'Jan':1,'Feb':2,'Mar':3,'Apr':4,'May':5,'Jun':6,'Jul':7,'Aug':8,'Sept':9,'Oct':10,'Nov':11,'Dec':12}
    for index, row in tt.iterrows():
        if row["Promo2"]==1:
            a = row['PromoInterval'].split(',')
            interval = map(lambda x: m[x],a)
            if row['Month'] in interval:
                rec[index] = 1
            else:
                g = np.array(interval)
                g = g+1
                if row['Month'] in g:
                    rec[index] = 2
                else:
                    rec[index] = 3
        else:
            pass
    tt["Promo2Month"] = rec
    #select attribute
    dt = np.asarray(tt[["Store","DayOfWeek","Promo","StateHoliday","SchoolHoliday","Year","Month","Day","CompetitionOpen","Promo2Open","Promo2Month","LogSales"]])
    #change values of stateholiday
    for row in dt:
        if row[3]=='0':
            row[3]=0
        elif row[3]=='a':
            row[3]=1
        elif row[3]=='b':
            row[3]=2
        else:
            row[3]=3
    #<type 'numpy.ndarray'>
    return dt

def test_data_preprocessing(t1,st):
    t1["Year"] = t1.Date.dt.year
    t1["Month"] = t1.Date.dt.month
    t1["Day"] = t1.Date.dt.day
    t1["WeekOfYear"] = t1.Date.dt.weekofyear
    #remove nans
    t1 = t1.fillna(1)
    t1 = pd.merge(t1, st, on='Store')

    rec = [0] * len(t1.index)
    for index, row in t1.iterrows():
        if row["CompetitionOpenSinceYear"]==0 or (row["Year"] - row["CompetitionOpenSinceYear"]>0):
            rec[index]=1
        elif row["Year"] - row["CompetitionOpenSinceYear"]==0:
            if row["Month"] - row["CompetitionOpenSinceMonth"] >= 0:
                rec[index] = 1
        else:
            pass
    t1["CompetitionOpen"] = rec

    rec = [0] * len(t1.index)
    for index, row in t1.iterrows():
        if row["Promo2"]== 1 and row["Year"] - row["Promo2SinceYear"] > 0:
            rec[index] = 1
        elif row["Promo2"]==1 and row["Year"] - row["Promo2SinceYear"] == 0:
            if row["WeekOfYear"] - row["Promo2SinceWeek"] >=0:
                rec[index] = 1
        else:
            pass
    t1["Promo2Open"] = rec

    rec = [4] * len(t1.index)
    m = {'Jan':1,'Feb':2,'Mar':3,'Apr':4,'May':5,'Jun':6,'Jul':7,'Aug':8,'Sept':9,'Oct':10,'Nov':11,'Dec':12}
    for index, row in t1.iterrows():
        if row["Promo2"]==1:
            a = row['PromoInterval'].split(',')
            interval = map(lambda x: m[x],a)
            if row['Month'] in interval:
                rec[index] = 1
            else:
                g = np.array(interval)
                g = g+1
                if row['Month'] in g:
                    rec[index] = 2
                else:
                    rec[index] = 3
        else:
            pass
    t1["Promo2Month"] = rec
    #t1 = t1[t1.Sales!=0]
    t1 = t1.sort("Id")
    td = np.asarray(t1[["Open","Store","DayOfWeek","Promo","StateHoliday","SchoolHoliday","Year","Month","Day","CompetitionOpen","Promo2Open","Promo2Month"]])#add "Sales" for testing
    #change values of stateholiday
    for row in td:
        if row[4]=='0':
            row[4]=0
        elif row[4]=='a':
            row[4]=1
        elif row[4]=='b':
            row[4]=2
        else:
            row[4]=3

    #<type 'numpy.ndarray'>
    return td

def rmspe(targets,predictions):
    return np.sqrt(np.mean(((predictions/(targets))-1)**2))
    #return np.sqrt((((targets-predictions)/(targets+1)) ** 2).mean())

########----main start---------------------:
#traind,testd = load_data()
traind = load_training_data()
testd = load_test_data()
std = load_store_data()
traindata = training_data_preprocessing(traind,std)
testdata = test_data_preprocessing(testd,std)

#--------training
#store id as keys
tables = {}
for row in traindata:
    if row[0] not in tables:
        tables[row[0]] = np.array([row[1:]])
    else:
        tables[row[0]] = np.append(tables[row[0]], np.array([row[1:]]), axis=0)

table_rf = {}
for key, table in tables.iteritems():
    x = [row[0:10] for row in table]
    y = [row[10] for row in table]
    #x, y = table[:,0:10], table[:,10]
    table_rf[key] = SVR()
    table_rf[key].fit(x, y)


#-------pridicting

pred = np.array([])
for idx in range(testdata.shape[0]):
    if testdata[idx][0] == 0:
        pred = np.append(pred, 0)
    else:
        rf_pred = table_rf[testdata[idx][1]].predict(testdata[idx][2:12])
        pred = np.append(pred, np.expm1(rf_pred))
'''
tg = np.array(testdata[:,12])
print "rmspe: "
print rmspe(tg, pred)
rul = pd.DataFrame(pred,tg,columns=['Pred'])
rul.to_csv("comp3.csv")
'''
rul = pd.DataFrame({ 'Id': range(1, len(pred)+1),'Sales': pred })
rul.to_csv("ross_svm.csv",index = False)
