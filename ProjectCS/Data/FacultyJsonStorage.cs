using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Text.Json.Nodes;

namespace SessionResultsCS
{
    public class FacultyJsonStorage : IFacultyStorage
    {
        private string _fileName;

        public FacultyJsonStorage(string fileName)
        {
            _fileName = fileName;
        }

        public Faculty Load()
        {
            string text = File.ReadAllText(_fileName);
            
            return JsonConvert.FacultyFromJson(JsonNode.Parse(text));
        }

        public void Save(Faculty faculty)
        {
            string text = JsonConvert.FacultyToJson(faculty).ToJsonString(
                new System.Text.Json.JsonSerializerOptions {
                    Encoder = System.Text.Encodings.Web.JavaScriptEncoder.UnsafeRelaxedJsonEscaping,
                    WriteIndented = true 
                }
            );

            File.WriteAllText(_fileName, text);
        }
    }
}
