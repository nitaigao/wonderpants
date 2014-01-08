#include "CCGB2ShapeCache.h"

#include "Box2D.h"
#include "Common.h"

 /**
 * Internal class to hold the fixtures
 */
class FixtureDef 
{
public:
  FixtureDef()
  : next(0)
  {}
  
  ~FixtureDef()
  {
    delete next;
    delete fixture.shape;
  }
  
  FixtureDef *next;
  b2FixtureDef fixture;
  int callbackData;
};

class BodyDef : public CCObject {
public:
  BodyDef() : fixtures(0) { };
  FixtureDef *fixtures;
  CCPoint anchorPoint;
};


static CCGB2ShapeCache* _sharedCache = 0;

CCGB2ShapeCache* CCGB2ShapeCache::sharedCache() {
  if (!_sharedCache) {
    _sharedCache = new CCGB2ShapeCache();
  }
  return _sharedCache;
}

CCPoint CCPointFromString(const String& str) {
  
  String theString = str;
  
  theString = theString.replace("{", "");
  theString = theString.replace("}", "");
  
  std::vector<String> array = theString.split(',');
  
  return CCPointMake(array[0].toFloat(), array[1].toFloat());    
}


void CCGB2ShapeCache::addShapedWithFile(const char* plist) {
  if (!shapeFiles.objectForKey(plist)) {
   
    const char* path = CCFileUtils::fullPathFromRelativePath(plist);
    
    CCDictionary<std::string, CCObject*>* dictionary = CCFileUtils::dictionaryWithContentsOfFile(path);
    
    CCDictionary<std::string, CCObject*>* metaDataDict = static_cast<CCDictionary<std::string, CCObject*>*>(dictionary->objectForKey("metadata"));
    
    float ptmRatio = static_cast<CCString*>(metaDataDict->objectForKey("ptm_ratio"))->toFloat();
    
    CCAssert(static_cast<CCString*>(metaDataDict->objectForKey("format"))->toInt() == 1, "Format not supported");
    
    CCDictionary<std::string, CCObject*>* bodyDict = (CCDictionary<std::string, CCObject*>*)dictionary->objectForKey("bodies");
    
    b2Vec2 vertices[b2_maxPolygonVertices];

    for (std::string& bodyName : bodyDict->allKeys()) {
      CCDictionary<std::string, CCObject*>* bodyData = (CCDictionary<std::string, CCObject*>*)bodyDict->objectForKey(bodyName);
      
      BodyDef* bodyDef = new BodyDef();
      bodyDef->anchorPoint = CCPointFromString(static_cast<CCString*>(bodyData->objectForKey("anchorpoint"))->toStdString());
      
      CCMutableArray<CCObject*>* fixtureList = static_cast<CCMutableArray<CCObject*>*>(bodyData->objectForKey("fixtures"));
      
      FixtureDef **nextFixtureDef = &(bodyDef->fixtures);
      
      for (int i = 0; i < fixtureList->count(); i++) {
        CCDictionary<std::string, CCObject*>* fixtureData = static_cast<CCDictionary<std::string, CCObject*>*>(fixtureList->getObjectAtIndex(i));

        b2FixtureDef basicData;
        
        basicData.filter.categoryBits = static_cast<CCString*>(fixtureData->objectForKey("filter_categoryBits"))->toFloat();
        basicData.filter.maskBits = static_cast<CCString*>(fixtureData->objectForKey("filter_maskBits"))->toInt();
        basicData.filter.groupIndex = static_cast<CCString*>(fixtureData->objectForKey("filter_groupIndex"))->toInt();
        basicData.friction = static_cast<CCString*>(fixtureData->objectForKey("friction"))->toFloat();
        basicData.density = static_cast<CCString*>(fixtureData->objectForKey("density"))->toFloat();
        basicData.restitution = static_cast<CCString*>(fixtureData->objectForKey("restitution"))->toFloat();
        basicData.isSensor = static_cast<CCString*>(fixtureData->objectForKey("isSensor"))->toInt();
//        int callbackData = static_cast<CCString*>(fixtureData->objectForKey("userdataCbValue"))->toInt();
        
        String fixtureType = static_cast<CCString*>(fixtureData->objectForKey("fixture_type"))->toStdString();
        
        if (fixtureType == "POLYGON") {
          CCMutableArray<CCObject*>* polygonsArray = static_cast<CCMutableArray<CCObject*>*>(fixtureData->objectForKey("polygons"));
          
          for (int i = 0; i < polygonsArray->count(); i++) {
            CCMutableArray<CCObject*>* polygonArray = static_cast<CCMutableArray<CCObject*>*>(polygonsArray->getObjectAtIndex(i));

            FixtureDef *fix = new FixtureDef();
            fix->fixture = basicData; // copy basic data
//            fix->callbackData = callbackData;
            
            b2PolygonShape *polyshape = new b2PolygonShape();
            int vindex = 0;
            
            assert(polygonArray->count() <= b2_maxPolygonVertices);
            
            for (int i = 0; i < polygonArray->count(); i++) {
              String pointString = static_cast<CCString*>(polygonArray->getObjectAtIndex(i))->toStdString();
              
              CCPoint offset = CCPointFromString(pointString);
              vertices[vindex].x = (offset.x / ptmRatio) ; 
              vertices[vindex].y = (offset.y / ptmRatio) ; 
              vindex++;
            }

            polyshape->Set(vertices, vindex);
            fix->fixture.shape = polyshape;
            
            // create a list
            *nextFixtureDef = fix;
            nextFixtureDef = &(fix->next);
          }
        }
        else
        {
          // circles are not yet supported
          assert(0);
        }

        shapeObjects.setObject(bodyDef, bodyName);
      }
    }
    
    CCString* bla = new CCString(plist);
    shapeFiles.setObject(bla, plist);
  }
}

void CCGB2ShapeCache::addFixturedToBody(b2Body* body, const char* key) {
  BodyDef *so = shapeObjects.objectForKey(key);
  assert(so);
  
  FixtureDef *fix = so->fixtures; 
  while(fix)
  {
    body->CreateFixture(&fix->fixture);
    fix = fix->next;
  }
}