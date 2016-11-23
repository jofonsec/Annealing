#1)Primero se incluyen los codigos

	#Incluye el directorio con tus propios codigos
	INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)

	#Incluye completamente la libreria ParadisEO
	INCLUDE_DIRECTORIES(${PARADISEO_INCLUDE_DIR})			
				    
#2)Define los ejecutables y dependencias
	
	ADD_EXECUTABLE(SA Annealing.cpp)
	ADD_DEPENDENCIES(SA lDiscovery)	

#3)Vincular las librerias para el ejecutable

	TARGET_LINK_LIBRARIES(SA ${PARADISEO_LIBRARIES} lDiscovery)

