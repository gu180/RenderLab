#ifndef _CPPUTIL_ENGINE_VIEWER_PLDM_GENERATOR_H_
#define _CPPUTIL_ENGINE_VIEWER_PLDM_GENERATOR_H_

#include <CppUtil/Basic/EleVisitor.h>
#include <CppUtil/OpenGL/FBO.h>
#include <CppUtil/OpenGL/Texture.h>
#include <CppUtil/OpenGL/VAO.h>
#include <CppUtil/OpenGL/Shader.h>

#include <CppUtil/Basic/Transform.h>

namespace CppUtil {
	namespace Engine {
		class Scene;
		class SObj;

		class Sphere;
		class Plane;
		class TriMesh;

		class CmptLight;

		class RasterBase;


		// Point Light Depth Map Generator
		class PLDM_Generator: public Basic::EleVisitor {
			ELEVISITOR_SETUP(PLDM_Generator)
		public:
			PLDM_Generator(RasterBase * raster);

			void Init();

			OpenGL::Texture GetDepthCubeMap(Basic::CPtr<CmptLight> light) const;
			float GetLightFar() const { return lightFar; }

		private:
			void Visit(Basic::Ptr<Scene> scene);
			void Visit(Basic::Ptr<SObj> sobj);

			void Visit(Basic::Ptr<Sphere> sphere);
			void Visit(Basic::Ptr<Plane> plane);
			void Visit(Basic::Ptr<TriMesh> mesh);

		private:
			RasterBase * raster;

			struct Val {
				Val(const OpenGL::FBO & fbo = OpenGL::FBO(), const OpenGL::Texture & tex = OpenGL::Texture())
					: fbo(fbo), tex(tex) { }

				OpenGL::FBO fbo;
				OpenGL::Texture tex;
			};
			std::map<Basic::WCPtr<CmptLight>, Val> lightMap;
			int depthMapSize;
			float lightFar;

			OpenGL::Shader shader_genDepth;
			std::vector<Transform> modelVec;
		};
	}
}

#endif//!_CPPUTIL_ENGINE_VIEWER_PLDM_GENERATOR_H_
