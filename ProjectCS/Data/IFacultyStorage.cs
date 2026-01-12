using System;
using System.Collections.Generic;
using System.Text;

namespace SessionResultsCS
{
    public interface IFacultyStorage
    {
        void Save(Faculty faculty);
        Faculty Load();
    }
}
