add_executable(Rhubarb 
    Core/CCamera.cpp
    Core/CEngine.cpp
    Core/CEntity.cpp
    Core/CMesh.cpp
    Core/CModel.cpp
    Core/CTriangleMesh.cpp

    Shaders/CDLShader.cpp
    Shaders/CFlatShader.cpp
    Shaders/CIdentityShader.cpp
    Shaders/CPhongShader.cpp
    Shaders/CShaderBase.cpp
    
    Helpers/CMatrixManager.cpp
    Helpers/CObjReader.cpp
    Helpers/CShaderManager.cpp
    Helpers/CTextureManager.cpp
    Helpers/CTimer.cpp
    
    Math/CMatrix44.cpp
    Math/CVector4.cpp
    
    main.cpp)
target_link_libraries(Rhubarb glut GLEW)
