#include "math/Hash.hpp"
#include <filesystem>
#define TINYOBJLOADER_IMPLEMENTATION
#include "rendering/MeshLoader.hpp"
#include "tiny_obj_loader.h"
#include <unordered_map>

namespace MeshLoader {
MeshData load(const std::filesystem::path &fileSource, VertexFormat format) {
  tinyobj::ObjReaderConfig reader_config;
  tinyobj::ObjReader reader;

  std::vector<float> vertices;
  std::vector<float> totalVertexData;
  std::vector<unsigned int> indices;

  glm::vec3 min(std::numeric_limits<float>::max());
  glm::vec3 max(std::numeric_limits<float>::lowest());

  // Disregarding typical concern that hashing floats is bad practice since we
  // will only take from given models.
  std::unordered_map<std::vector<float>, unsigned int, VectorHasher<float>>
      vertexToIndex;

  if (!reader.ParseFromFile(fileSource, reader_config)) {
    throw std::runtime_error(std::string("TinyObjReader: " + reader.Error()));
  }

  auto &attrib = reader.GetAttrib();
  auto &shapes = reader.GetShapes();

  for (size_t s = 0; s < shapes.size(); s++) {
    size_t index_offset = 0;
    for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
      size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

      for (size_t v = 0; v < fv; v++) {
        vertices.clear();

        tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

        tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
        vertices.push_back(vx);

        if (vx < min.x) {
          min.x = vx;
        } else if (vx > max.x) {
          max.x = vx;
        }

        tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
        vertices.push_back(vy);

        if (vy < min.y) {
          min.y = vy;
        } else if (vy > max.y) {
          max.y = vy;
        }

        tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
        vertices.push_back(vz);

        if (vz < min.z) {
          min.z = vz;
        } else if (vz > max.z) {
          max.z = vz;
        }

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

        if (!vertexToIndex.count(vertices)) {
          unsigned int currentSize = vertexToIndex.size();

          indices.push_back(currentSize);
          vertexToIndex.insert({vertices, currentSize});

          totalVertexData.push_back(vx);
          totalVertexData.push_back(vy);
          totalVertexData.push_back(vz);
        } else {
          indices.push_back(vertexToIndex.at(vertices));
        }
      }
      index_offset += fv;
    }
  }
  return MeshData(totalVertexData, indices, min, max);
}
} // namespace MeshLoader
