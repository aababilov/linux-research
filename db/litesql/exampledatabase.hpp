#ifndef _exampledatabase_hpp_
#define _exampledatabase_hpp_
#include <litesql.hpp>
namespace example {
class user;
class Person;
class Role;
class Student;
class Employee;
class School;
class Office;
class PersonPersonRelationMother {
public:
    class Row {
    public:
        litesql::Field<int> intfld;
        litesql::Field<int> person2;
        litesql::Field<int> person1;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType Person1;
    static const litesql::FieldType Person2;
    static const litesql::FieldType Intfld;
    static void link(const litesql::Database& db, const example::Person& o0, const example::Person& o1, int intfld);
    static void unlink(const litesql::Database& db, const example::Person& o0, const example::Person& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<PersonPersonRelationMother::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<litesql::PersistentPtr<example::Person> > getPerson1(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
    static litesql::DataSource<litesql::PersistentPtr<example::Person> > getPerson2(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
};
class PersonPersonRelationFather {
public:
    class Row {
    public:
        litesql::Field<int> person2;
        litesql::Field<int> person1;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType Person1;
    static const litesql::FieldType Person2;
    static void link(const litesql::Database& db, const example::Person& o0, const example::Person& o1);
    static void unlink(const litesql::Database& db, const example::Person& o0, const example::Person& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<PersonPersonRelationFather::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<litesql::PersistentPtr<example::Person> > getPerson1(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
    static litesql::DataSource<litesql::PersistentPtr<example::Person> > getPerson2(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
};
class PersonPersonRelationSiblings {
public:
    class Row {
    public:
        litesql::Field<int> person2;
        litesql::Field<int> person1;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType Person1;
    static const litesql::FieldType Person2;
    static void link(const litesql::Database& db, const example::Person& o0, const example::Person& o1);
    static void unlink(const litesql::Database& db, const example::Person& o0, const example::Person& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<PersonPersonRelationSiblings::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<litesql::PersistentPtr<example::Person> > getPerson1(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
    static litesql::DataSource<litesql::PersistentPtr<example::Person> > getPerson2(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
};
class PersonPersonRelationChildren {
public:
    class Row {
    public:
        litesql::Field<int> person2;
        litesql::Field<int> person1;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType Person1;
    static const litesql::FieldType Person2;
    static void link(const litesql::Database& db, const example::Person& o0, const example::Person& o1);
    static void unlink(const litesql::Database& db, const example::Person& o0, const example::Person& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<PersonPersonRelationChildren::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<litesql::PersistentPtr<example::Person> > getPerson1(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
    static litesql::DataSource<litesql::PersistentPtr<example::Person> > getPerson2(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
};
class RoleRelation {
public:
    class Row {
    public:
        litesql::Field<int> role;
        litesql::Field<int> person;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType Person;
    static const litesql::FieldType Role;
    static void link(const litesql::Database& db, const example::Person& o0, const example::Role& o1);
    static void unlink(const litesql::Database& db, const example::Person& o0, const example::Role& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<RoleRelation::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    template <class T> static litesql::DataSource<T> get(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
};
class SchoolStudentRelation {
public:
    class Row {
    public:
        litesql::Field<int> student;
        litesql::Field<int> school;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType School;
    static const litesql::FieldType Student;
    static void link(const litesql::Database& db, const example::School& o0, const example::Student& o1);
    static void unlink(const litesql::Database& db, const example::School& o0, const example::Student& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<SchoolStudentRelation::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    template <class T> static litesql::DataSource<T> get(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
};
class EmployeeOfficeRelation {
public:
    class Row {
    public:
        litesql::Field<int> office;
        litesql::Field<int> employee;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType Employee;
    static const litesql::FieldType Office;
    static void link(const litesql::Database& db, const example::Employee& o0, const example::Office& o1);
    static void unlink(const litesql::Database& db, const example::Employee& o0, const example::Office& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<EmployeeOfficeRelation::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    template <class T> static litesql::DataSource<T> get(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
};
class user : public litesql::Persistent {
    friend class litesql::PersistentPtr<user>;
    friend class ExampleDatabase;
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    static const litesql::FieldType Type;
    static const litesql::FieldType Name;
    litesql::Field<std::string> name;
    static const litesql::FieldType Passwd;
    litesql::Field<std::string> passwd;
protected:
    void defaults();
    user(const litesql::Database& db, const std::string& type=type__);
    user(const litesql::Database& db, const litesql::Record& rec);
public:
    void sayHello();
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect();
};
std::ostream & operator<<(std::ostream& os, const user& o);
class Person : public litesql::Persistent {
    friend class litesql::PersistentPtr<Person>;
    friend class ExampleDatabase;
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    class SexType : public litesql::FieldType {
    public:
        static const int Male;
        static const int Female;
        SexType(const std::string& n, const std::string& t, const std::string& tbl, const litesql::FieldType::Values& vals=Values());
    };
    class Sex {
    public:
        static const int Male;
        static const int Female;
    };
    class MotherHandle : public litesql::RelationHandle<Person> {
    public:
        MotherHandle(const Person& owner);
        void link(const Person& o0, int intfld);
        void unlink(const Person& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<litesql::PersistentPtr<Person> > get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<PersonPersonRelationMother::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    class FatherHandle : public litesql::RelationHandle<Person> {
    public:
        FatherHandle(const Person& owner);
        void link(const Person& o0);
        void unlink(const Person& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<litesql::PersistentPtr<Person> > get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<PersonPersonRelationFather::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    class SiblingsHandle : public litesql::RelationHandle<Person> {
    public:
        SiblingsHandle(const Person& owner);
        void link(const Person& o0);
        void unlink(const Person& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<litesql::PersistentPtr<Person> > get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<PersonPersonRelationSiblings::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    class ChildrenHandle : public litesql::RelationHandle<Person> {
    public:
        ChildrenHandle(const Person& owner);
        void link(const Person& o0);
        void unlink(const Person& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<litesql::PersistentPtr<Person> > get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<PersonPersonRelationChildren::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    class RolesHandle : public litesql::RelationHandle<Person> {
    public:
        RolesHandle(const Person& owner);
        void link(const Role& o0);
        void unlink(const Role& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<litesql::PersistentPtr<Role> > get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<RoleRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    static const litesql::FieldType Type;
    static const litesql::FieldType Name;
    litesql::Field<std::string> name;
    static const litesql::FieldType Age;
    litesql::Field<int> age;
    static const litesql::FieldType Image;
    litesql::Field<litesql::Blob> image;
protected:
    static std::vector < std::pair< std::string, std::string > > sex_values;
public:
    static const Person::SexType Sex;
    litesql::Field<int> sex;
    static void initValues();
protected:
    void defaults();
    Person(const litesql::Database& db, const std::string& type=type__);
    Person(const litesql::Database& db, const litesql::Record& rec);
public:
    Person::MotherHandle mother();
    Person::FatherHandle father();
    Person::SiblingsHandle siblings();
    Person::ChildrenHandle children();
    Person::RolesHandle roles();
    void sayHello();
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect();
};
std::ostream & operator<<(std::ostream& os, const Person& o);
class Role : public litesql::Persistent {
    friend class litesql::PersistentPtr<Role>;
    friend class ExampleDatabase;
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    class PersonHandle : public litesql::RelationHandle<Role> {
    public:
        PersonHandle(const Role& owner);
        void link(const Person& o0);
        void unlink(const Person& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<litesql::PersistentPtr<Person> > get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<RoleRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    static const litesql::FieldType Type;
protected:
    void defaults();
    Role(const litesql::Database& db, const std::string& type=type__);
    Role(const litesql::Database& db, const litesql::Record& rec);
public:
    Role::PersonHandle person();
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect();
};
std::ostream & operator<<(std::ostream& os, const Role& o);
class Student : public Role {
    friend class litesql::PersistentPtr<Student>;
    friend class ExampleDatabase;
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    class SchoolHandle : public litesql::RelationHandle<Student> {
    public:
        SchoolHandle(const Student& owner);
        void link(const School& o0);
        void unlink(const School& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<litesql::PersistentPtr<School> > get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<SchoolStudentRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    static const std::string type__;
    static const std::string table__;
protected:
    Student(const litesql::Database& db, const std::string& type=type__);
    Student(const litesql::Database& db, const litesql::Record& rec);
public:
    Student::SchoolHandle school();
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect();
};
std::ostream & operator<<(std::ostream& os, const Student& o);
class Employee : public Role {
    friend class litesql::PersistentPtr<Employee>;
    friend class ExampleDatabase;
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    class OfficeHandle : public litesql::RelationHandle<Employee> {
    public:
        OfficeHandle(const Employee& owner);
        void link(const Office& o0);
        void unlink(const Office& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<litesql::PersistentPtr<Office> > get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<EmployeeOfficeRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    static const std::string type__;
    static const std::string table__;
protected:
    Employee(const litesql::Database& db, const std::string& type=type__);
    Employee(const litesql::Database& db, const litesql::Record& rec);
public:
    Employee::OfficeHandle office();
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect();
};
std::ostream & operator<<(std::ostream& os, const Employee& o);
class School : public litesql::Persistent {
    friend class litesql::PersistentPtr<School>;
    friend class ExampleDatabase;
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    class StudentsHandle : public litesql::RelationHandle<School> {
    public:
        StudentsHandle(const School& owner);
        void link(const Student& o0);
        void unlink(const Student& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<litesql::PersistentPtr<Student> > get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<SchoolStudentRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    static const litesql::FieldType Type;
    static const litesql::FieldType Name;
    litesql::Field<std::string> name;
protected:
    void defaults();
    School(const litesql::Database& db, const std::string& type=type__);
    School(const litesql::Database& db, const litesql::Record& rec);
public:
    School::StudentsHandle students();
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect();
};
std::ostream & operator<<(std::ostream& os, const School& o);
class Office : public litesql::Persistent {
    friend class litesql::PersistentPtr<Office>;
    friend class ExampleDatabase;
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    class EmployeesHandle : public litesql::RelationHandle<Office> {
    public:
        EmployeesHandle(const Office& owner);
        void link(const Employee& o0);
        void unlink(const Employee& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<litesql::PersistentPtr<Employee> > get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<EmployeeOfficeRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    static const litesql::FieldType Type;
protected:
    void defaults();
    Office(const litesql::Database& db, const std::string& type=type__);
    Office(const litesql::Database& db, const litesql::Record& rec);
public:
    Office::EmployeesHandle employees();
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect();
};
std::ostream & operator<<(std::ostream& os, const Office& o);
class ExampleDatabase : public litesql::Database {
public:
    ExampleDatabase(std::string backendType, std::string connInfo);
protected:
    virtual std::vector<litesql::Database::SchemaItem> getSchema() const;
    static void initialize();
public:
    virtual litesql::Persistent* createPersistent(const litesql::Record& rec) const;
};
}
#endif
