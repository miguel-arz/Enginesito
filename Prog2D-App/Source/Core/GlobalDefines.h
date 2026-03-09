#pragma once

#define DERIVED_CLASS(myclass, base) \
typedef base Super;

#define UNUSED_VARIABLE(var) (void)var;

#define LILA       CLITERAL(Color){ 200, 162, 200, 255 }
#define LAVANDA    CLITERAL(Color){ 200, 160, 225, 255 }

#define EPS_1 (0.1f)

#define EPS_3 (0.001f)

#define EPS_5 (0.00001f)



//-------------------------

//#define START_DESERIALIZATION(oDoc) \
//pugi::xml_node oRootNode = oDoc.first_child(); \
//if (oRootNode && strcmp(oRootNode.name(), "CAction") == 0)\
//{
//
//#define END_DESERIALIZATION() }
//
//
//#define GET_ATTRIBUTE(type, sVarName, sAttName, DefaultValue) \
//if (pugi::xml_attribute oAtt = oNode.attribute(#sAttName)) \
//{ \
//  sVarName = oAtt.as_##type(); \
//} \
//else \
//{ \
//  sVarName = DefaultValue; \
//} \
//
//#define GET_VARIABLE(type, sVarName, sNodeName, sAttName, DefaultValue) \
//if (pugi::xml_node oNode = oRootNode.find_child([](const pugi::xml_node& _oNode) { return strcmp(_oNode.name(), #sNodeName) == 0;})) \
//{ \
//  GET_ATTRIBUTE(type, sVarName, sAttName, DefaultValue) \
//}\
//else \
//{ \
//sVarName = DefaultValue; \
//}
//
//#define GET_ATTRIBUTE_WITH_ERROR(type, sVarName, sAttName, DefaultValue, ErrorMsg) \
//if (pugi::xml_attribute oAtt = oNode.attribute(#sAttName)) \
//{ \
//  sVarName = oAtt.as_##type(); \
//} \
//else \
//{ \
//  sVarName = DefaultValue; \
//  TraceLog(LOG_ERROR, ErrorMsg); \
//} \
//
//#define GET_VARIABLE_WITH_ERROR(type, sVarName, sNodeName, sAttName, DefaultValue, ErrorMsg) \
//if (pugi::xml_node oNode = oRootNode.find_child([](const pugi::xml_node& _oNode) { return strcmp(_oNode.name(), #sNodeName) == 0;})) \
//{ \
//  GET_ATTRIBUTE_WITH_ERROR(type, sVarName, sAttName, DefaultValue, ErrorMsg) \
//} \
//else \
//{ \
//  sVarName = DefaultValue; \
//  TraceLog(LOG_ERROR, ErrorMsg); \
//} 
//
//
//#define CREATE_COLLECTION(type, sCollectionVarName, sCollectionNodeName) \
//if (pugi::xml_node oChild = oRootNode.find_child([](const pugi::xml_node& _oNode) { return strcmp(_oNode.name(), #sCollectionNodeName) == 0;})) \
//{ \
//  for (; oChild; oChild = oChild.next_sibling()) \
//  { \
//    sCollectionVarName.emplace_back(oChild); \
//  } \
//}
//
//
//
//#define GET_VARIABLE_VALUE(type, sVarName, sNodeName, DefaultValue) GET_VARIABLE(type, sVarName, sNodeName, Value, DefaultValue)
//#define GET_VARIABLE_VALUE_WITH_ERROR(type, sVarName, sNodeName, DefaultValue, ErrorMsg) GET_VARIABLE_WITH_ERROR(type, sVarName, sNodeName, Value, DefaultValue, ErrorMsg)
//
//#define GET_VARIABLE_AS_VECTOR2(sVarName, sNodeName, sAttX, sAttY, DefaultValueX, DefaultValueY) \
//GET_VARIABLE(float, sVarName.x, sNodeName, sAttX, DefaultValueX) \
//GET_VARIABLE(float, sVarName.y, sNodeName, sAttY, DefaultValueY) 
//
//#define GET_VARIABLE_AS_VECTOR3(sVarName, sNodeName, sAttX, sAttY, sAttZ, DefaultValueX, DefaultValueY, DefaultValueZ) \
//GET_VARIABLE_AS_VECTOR2(sVarName, sNodeName, sAttX, sAttY, DefaultValueX, DefaultValueY) \
//GET_VARIABLE(float, sVarName.z, sNodeName, sAttZ, DefaultValueZ) 
//
//#define GET_VARIABLE_AS_VECTOR4(sVarName, sNodeName, sAttX, sAttY, sAttZ, sAttW, DefaultValueX, DefaultValueY, DefaultValueZ, DefaultValueW) \
//GET_VARIABLE_AS_VECTOR3(sVarName, sNodeName, sAttX, sAttY, sAttZ, DefaultValueX, DefaultValueY, DefaultValueZ) \
//GET_VARIABLE(float, sVarName.w, sNodeName, sAttW, DefaultValueW) 
//
//
/////------------------------------
//#define GET_ATTRIBUTE_VALUE(type, sVarName, DefaultValue) GET_ATTRIBUTE(type, sVarName, Value, DefaultValue)
//#define GET_ATTRIBUTE_VALUE_WITH_ERROR(type, sVarName, DefaultValue, ErrorMsg) GET_ATTRIBUTE_WITH_ERROR(type, sVarName, Value, DefaultValue, ErrorMsg)
//
//#define GET_ATTRIBUTE_AS_VECTOR2(sVarName, sAttX, sAttY, DefaultValueX, DefaultValueY) \
//GET_ATTRIBUTE(float, sVarName.x, sAttX, DefaultValueX) \
//GET_ATTRIBUTE(float, sVarName.y, sAttY, DefaultValueY) 
//
//#define GET_ATTRIBUTE_AS_VECTOR3(sVarName, sAttX, sAttY, sAttZ, DefaultValueX, DefaultValueY, DefaultValueZ) \
//GET_ATTRIBUTE_AS_VECTOR2(sVarName, sAttX, sAttY, DefaultValueX, DefaultValueY) \
//GET_ATTRIBUTE(float, sVarName.z, sAttZ, DefaultValueZ) 
//
//#define GET_ATTRIBUTE_AS_VECTOR4(sVarName, sAttX, sAttY, sAttZ, sAttW, DefaultValueX, DefaultValueY, DefaultValueZ, DefaultValueW) \
//GET_ATTRIBUTE_AS_VECTOR3(sVarName, sAttX, sAttY, sAttZ, DefaultValueX, DefaultValueY, DefaultValueZ) \
//GET_ATTRIBUTE(float, sVarName.w, sAttW, DefaultValueW) 



//------------------------------
#define START_DESERIALIZATION(sFilePath, oDoc, sName, sExtension) \
{ \
if (strstr(sFilePath, #sExtension)) \
{ \
	pugi::xml_document oDoc; \
	pugi::xml_parse_result oResult = oDoc.load_file(sFilePath); \
	if (oResult) \
	{ \
		pugi::xml_node oRoot = oDoc.first_child(); \
		if (oRoot && strcmp(oRoot.name(), #sName) == 0) \
		{ 

#define END_DESERIALIZATION(sErrorMsg) \
		} \
	} \
	else { \
		\
		TraceLog(LOG_ERROR, oResult.description()); \
	} \
} \
else \
{ \
	TraceLog(LOG_ERROR, sErrorMsg); \
} \
}

#define GET_NODE(sVarName, sParentVarName, sNodeName) \
pugi::xml_node sVarName = sParentVarName.find_child([](const pugi::xml_node& _oNode) \
	{ return strcmp(_oNode.name(), #sNodeName) == 0; })

#define FOR_EACH_CHILD_NODE(sVarName, sParentNodeVar, sNodeName) \
for(GET_NODE(sVarName, sParentNodeVar, sNodeName); sVarName; sVarName = sVarName.next_sibling(#sNodeName)) { \

#define END_FOR_EACH_CHILD_NODE }

#define GET_ATTRIBUTE(type, sVarName, sAttName, defaultValue) \
if (pugi::xml_attribute oValue = oNode.attribute(#sAttName)) \
{ \
	sVarName = oValue.as_##type(); \
} \
else \
{ \
	sVarName = defaultValue; \
} \

#define GET_ATTRIBUTE_WITH_ERROR(type, sVarName, sAttName, defaultValue, sErrorMsg) \
if (pugi::xml_attribute oValue = oNode.attribute(#sAttName)) \
{ \
	sVarName = oValue.as_##type(); \
} \
else \
{ \
	sVarName = defaultValue; \
	TraceLog(LOG_ERROR, sErrorMsg); \
} \

#define GET_VARIABLE(type, sVarName, sNodeName, sAttName, defaultValue) \
if (pugi::xml_node oNode = oRoot.find_child([](const pugi::xml_node& _oNode) \
	{ return strcmp(_oNode.name(), #sNodeName) == 0; })) \
{ \
	GET_ATTRIBUTE(type, sVarName, sAttName, defaultValue) \
} \
else \
{ \
	sVarName = defaultValue; \
}

#define GET_VARIABLE_WITH_ERROR(type, sVarName, sNodeName, sAttName, defaultValue, sErrorMsg) \
if (pugi::xml_node oNode = oRoot.find_child([](const pugi::xml_node& _oNode) \
	{ return strcmp(_oNode.name(), #sNodeName) == 0; })) \
{ \
	GET_ATTRIBUTE_WITH_ERROR(type, sVarName, sAttName, defaultValue, sErrorMsg) \
} \
else \
{ \
	sVarName = defaultValue; \
	TraceLog(LOG_ERROR, sErrorMsg); \
}

#define GET_ENUM_VARIABLE(type, sVarName, sNodeName, sAttName, defaultValue) \
{ \
const char* sEnum {"Null"}; \
GET_VARIABLE(string, sEnum, sNodeName, sAttName, "Null") \
if (sEnum == "Null") \
{ \
	sVarName = defaultValue; \
} \
else \
{ \
	sVarName = type::AsEnum(sEnum); \
} \
}

#define GET_ENUM_VARIABLE_WITH_ERROR(type, sVarName, sNodeName, sAttName, defaultValue, sErrorMsg) \
{ \
const char* sEnum {"Null"}; \
GET_VARIABLE(string, sEnum, sNodeName, sAttName, "Null") \
if (sEnum == "Null") \
{ \
	sVarName = defaultValue; \
	TraceLog(LOG_ERROR, sErrorMsg); \
} \
else \
{ \
	sVarName = type::AsEnum(sEnum); \
} \
}

#define GET_VARIABLE_VALUE(type, sVarName, sNodeName, defaultValue) GET_VARIABLE(type, sVarName, sNodeName, value, defaultValue)
#define GET_VARIABLE_VALUE_WITH_ERROR(type, sVarName, sNodeName, defaultValue, sErrorMsg) GET_VARIABLE_WITH_ERROR(type, sVarName, sNodeName, value, defaultValue, sErrorMsg)

#define GET_VARIABLE_AS_VECTOR2(sVarName, sNodeName, sAttX, sAttY, defaultValueX, defaultValueY) \
GET_VARIABLE(float, sVarName.x, sNodeName, sAttX, defaultValueX) \
GET_VARIABLE(float, sVarName.y, sNodeName, sAttY, defaultValueY)

#define GET_VARIABLE_AS_VECTOR3(sVarName, sNodeName, sAttX, sAttY, sAttZ, defaultValueX, defaultValueY, defaultValueZ) \
GET_VARIABLE_AS_VECTOR2(sVarName, sNodeName, sAttX, sAttY, defaultValueX, defaultValueY) \
GET_VARIABLE(float, sVarName.z, sNodeName, sAttZ, defaultValueZ)

#define GET_VARIABLE_AS_VECTOR4(sVarName, sNodeName, sAttX, sAttY, sAttZ, sAttW, defaultValueX, defaultValueY, defaultValueZ, defaultValueW) \
GET_VARIABLE_AS_VECTOR3(sVarName, sNodeName, sAttX, sAttY, sAttZ, defaultValueX, defaultValueY, defaultValueZ) \
GET_VARIABLE(float, sVarName.w, sNodeName, sAttW, defaultValueW)

#define GET_ATTRIBUTES_AS_VECTOR2(sVarName, sAttX, sAttY, defaultValueX, defaultValueY) \
GET_ATTRIBUTE(float, sVarName.x, sAttX, defaultValueX) \
GET_ATTRIBUTE(float, sVarName.y, sAttY, defaultValueY)

#define GET_ATTRIBUTES_AS_VECTOR3(sVarName, sAttX, sAttY, sAttZ, defaultValueX, defaultValueY, defaultValueZ) \
GET_ATTRIBUTES_AS_VECTOR2(sVarName, sAttX, sAttY, defaultValueX, defaultValueY) \
GET_ATTRIBUTE(float, sVarName.z, sAttZ, defaultValueZ)

#define GET_ATTRIBUTES_AS_VECTOR4(sVarName, sAttX, sAttY, sAttZ, sAttW, defaultValueX, defaultValueY, defaultValueZ, defaultValueW) \
GET_ATTRIBUTES_AS_VECTOR3(sVarName, sAttX, sAttY, sAttZ, defaultValueX, defaultValueY, defaultValueZ) \
GET_ATTRIBUTE(float, sVarName.w, sAttW, defaultValueW)

#define GET_ENUM_VARIABLE_VALUE(type, sVarName, sNodeName, defaultValue) GET_ENUM_VARIABLE(type, sVarName, sNodeName, value, defaultValue)
#define GET_ENUM_VARIABLE_VALUEWITH_ERROR(type, sVarName, sNodeName, defaultValue, sErrorMsg) GET_ENUM_VARIABLE_WITH_ERROR(type, sVarName, sNodeName, value, defaultValue, sErrorMsg)

#define GET_COLLECTION(sCollectionVarName, oNode) \
for (pugi::xml_node oChild = oNode.first_child(); oChild; oChild = oChild.next_sibling()) \
{ \
	sCollectionVarName.emplace_back(oChild); \
} 

#define GET_VARIABLE_COLLECTION(sCollectionVarName, sCollectionNodeName) \
if (pugi::xml_node oCollectionNode = oRoot.find_child([](const pugi::xml_node& _oNode) \
	{ return strcmp(_oNode.name(), #sCollectionNodeName) == 0;})) \
{ \
	GET_COLLECTION(sCollectionVarName, oCollectionNode) \
}

#define ADD_COMPONENTS_COLLECTION(oEntity, sCollectionNodeName) \
if (pugi::xml_node oCollectionNode = oRoot.find_child([](const pugi::xml_node& _oNode) \
	{ return strcmp(_oNode.name(), #sCollectionNodeName) == 0;})) \
{ \
  for (pugi::xml_node oChild = oCollectionNode.first_child(); oChild; oChild = oChild.next_sibling()) \
  { \
	const char* sComponentType {""}; \
	pugi::xml_node oNode{oChild}; \
	GET_ATTRIBUTE(string, sComponentType, sType, ""); \
	if(strcmp(sComponentType, "SpriteRendererComponent") == 0) \
	{ \
		(oEntity).AddComponent<CSpriteRendererComponent>(oChild); \
	} \
	else if (strcmp(sComponentType, "AnimationComponent") == 0) \
	{ \
		(oEntity).AddComponent<CAnimationComponent>(oChild); \
	} \
	else if (strcmp(sComponentType, "TileMapRendererComponent") == 0) \
	{ \
		(oEntity).AddComponent<CTileMapRendererComponent>(oChild); \
	} \
	else if (strcmp(sComponentType, "ControllerComponent") == 0) \
	{ \
		(oEntity).AddComponent<CControllerComponent>(oChild); \
	} \
  } \
}

#define GET_LAYER_PROPERTY(type, sVarName, oLayerNode, sPropertyName, defaultValue) \
	GET_NODE(oPropertiesNode, oLayerNode, properties); \
	if(oPropertiesNode) \
	{ \
		FOR_EACH_CHILD_NODE(oNode, oPropertiesNode, property) \
			if(std::strcmp(oNode.attribute("name").as_string(), #sPropertyName) == 0) \
			{ \
				GET_ATTRIBUTE(type, sVarName, value, defaultValue) \
			} \
		END_FOR_EACH_CHILD_NODE \
	}

