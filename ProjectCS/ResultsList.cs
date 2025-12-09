using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Numerics;


namespace SessionResultsCS
{
    public class ResultsList<T> : IEnumerable<T> where T : AttestationResult?
    {
        private List<T> _results;


        public ResultsList()
        {
            _results = new List<T>();
        }

        public ResultsList(IEnumerable<T> results)
        {
            _results = new List<T>(results);
        }

        public ResultsList(IEnumerable<Student> students, Discipline discipline)
        {
            _results = new List<T>();
            AddStudentsResults(students, discipline);
        }

        public void Add(T result)
        {
            _results.Add(result);
        }

        public void AddRange(IEnumerable<T> results)
        {
            _results.AddRange(results);
        }

        public void AddStudentsResults(IEnumerable<Student> students, Discipline discipline)
        {
            _results.AddRange(students.Select(student =>
            {
                if (student.SessionResults.GetResult(discipline) is T result)
                {
                    return result;
                }
                else
                {
                    throw new ArgumentException("Student has result of wrong type");
                }
            }));
        }

        public int GetSize()
        {
            return _results.Count;
        }

        public ReadOnlyCollection<T> GetResults()
        {
            return _results.AsReadOnly();
        }

        public int AverageScore()
        {
            return EnumerableAverage(_results.Select(res => res?.ToScore() ?? 0));
        }

        public double PassedPercent()
        {
            return EnumerableAverage(_results.Select(res => (res is not null && res.IsPassed()) ? 1.0 : 0.0)) * 100.0;
        }

        public IEnumerator<T> GetEnumerator()
        {
            return _results.GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }


        static TNumber EnumerableAverage<TNumber>(IEnumerable<TNumber> values) where TNumber : INumber<TNumber>
        {
            var (sum, size) = values.Aggregate((Sum: TNumber.Zero, Size: 0), (acc, val) => (acc.Sum + val, acc.Size + 1));
            return size == 0 ? TNumber.Zero : sum / TNumber.CreateChecked(size);
        }
    }
}
