#include <filesystem>
#define TINYOBJLOADER_IMPLEMENTATION
#include "rendering/MeshLoader.hpp"
#include "tiny_obj_loader.h"

namespace MeshLoader {
std::vector<float> load(const std::filesystem::path &fileSource,
                        VertexFormat format) {
  std::vector<float> vertexData;
  tinyobj::ObjReaderConfig reader_config;
  tinyobj::ObjReader reader;

  if (!reader.ParseFromFile(fileSource, reader_config)) {
    if (!reader.Error().empty()) {
      throw std::runtime_error(std::string("TinyObjReader: " + reader.Error()));
    }
  }

  auto &attrib = reader.GetAttrib();
  auto &shapes = reader.GetShapes();

  for (size_t s = 0; s < shapes.size(); s++) {
    size_t index_offset = 0;
    for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
      size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

      for (size_t v = 0; v < fv; v++) {
        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
        tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
        vertexData.push_back(vx);
        tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
        vertexData.push_back(vy);
        tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
        vertexData.push_back(vz);

        // TODO: ONCE SUPPORT FOR NORMAL AND (maybe) TEXTURES ARE ADDED,
        // UNCOMMENT!

        // Check if `normal_index` is zero or positive. negative = no normal
        // data
        // if (idx.normal_index >= 0) {
        //   tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) +
        //   0]; tinyobj::real_t ny = attrib.normals[3 *
        //   size_t(idx.normal_index) + 1]; tinyobj::real_t nz =
        //   attrib.normals[3 * size_t(idx.normal_index) + 2];
        // }

        // Check if `texcoord_index` is zero or positive. negative = no texcoord
        // data
        // if (idx.texcoord_index >= 0) {
        //   tinyobj::real_t tx =
        //       attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
        //   tinyobj::real_t ty =
        //       attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
        // }
      }
      index_offset += fv;
    }
  }
  return vertexData;
}
} // namespace MeshLoader
