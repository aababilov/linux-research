#include "exampledatabase.hpp"
namespace example {
using namespace litesql;
PersonPersonRelationMother::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : intfld(PersonPersonRelationMother::Intfld), person2(PersonPersonRelationMother::Person2), person1(PersonPersonRelationMother::Person1) {
    switch(rec.size()) {
    case 3:
        intfld = rec[2];
    case 2:
        person2 = rec[1];
    case 1:
        person1 = rec[0];
    }
}
const std::string PersonPersonRelationMother::table__("Person_Person_Mother");
const litesql::FieldType PersonPersonRelationMother::Person1("Person1","INTEGER",table__);
const litesql::FieldType PersonPersonRelationMother::Person2("Person2","INTEGER",table__);
const litesql::FieldType PersonPersonRelationMother::Intfld("intfld_","INTEGER",table__);
void PersonPersonRelationMother::link(const litesql::Database& db, const example::Person& o0, const example::Person& o1, int intfld) {
    Record values;
    Split fields;
    fields.push_back(Person1.name());
    values.push_back(o0.id);
    fields.push_back(Person2.name());
    values.push_back(o1.id);
    fields.push_back(Intfld.name());
    values.push_back(toString(intfld));
    db.insert(table__, values, fields);
}
void PersonPersonRelationMother::unlink(const litesql::Database& db, const example::Person& o0, const example::Person& o1) {
    db.delete_(table__, (Person1 == o0.id && Person2 == o1.id));
}
void PersonPersonRelationMother::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<PersonPersonRelationMother::Row> PersonPersonRelationMother::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Person1.fullName());
    sel.result(Person2.fullName());
    sel.result(Intfld.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<PersonPersonRelationMother::Row>(db, sel);
}
litesql::DataSource<litesql::PersistentPtr<example::Person> > PersonPersonRelationMother::getPerson1(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Person1.fullName());
    sel.where(srcExpr);
    return litesql::DataSource<litesql::PersistentPtr<example::Person> >(db, example::Person::Id.in(sel) && expr);
}
litesql::DataSource<litesql::PersistentPtr<example::Person> > PersonPersonRelationMother::getPerson2(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Person2.fullName());
    sel.where(srcExpr);
    return litesql::DataSource<litesql::PersistentPtr<example::Person> >(db, example::Person::Id.in(sel) && expr);
}
PersonPersonRelationFather::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : person2(PersonPersonRelationFather::Person2), person1(PersonPersonRelationFather::Person1) {
    switch(rec.size()) {
    case 2:
        person2 = rec[1];
    case 1:
        person1 = rec[0];
    }
}
const std::string PersonPersonRelationFather::table__("Person_Person_Father");
const litesql::FieldType PersonPersonRelationFather::Person1("Person1","INTEGER",table__);
const litesql::FieldType PersonPersonRelationFather::Person2("Person2","INTEGER",table__);
void PersonPersonRelationFather::link(const litesql::Database& db, const example::Person& o0, const example::Person& o1) {
    Record values;
    Split fields;
    fields.push_back(Person1.name());
    values.push_back(o0.id);
    fields.push_back(Person2.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void PersonPersonRelationFather::unlink(const litesql::Database& db, const example::Person& o0, const example::Person& o1) {
    db.delete_(table__, (Person1 == o0.id && Person2 == o1.id));
}
void PersonPersonRelationFather::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<PersonPersonRelationFather::Row> PersonPersonRelationFather::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Person1.fullName());
    sel.result(Person2.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<PersonPersonRelationFather::Row>(db, sel);
}
litesql::DataSource<litesql::PersistentPtr<example::Person> > PersonPersonRelationFather::getPerson1(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Person1.fullName());
    sel.where(srcExpr);
    return litesql::DataSource<litesql::PersistentPtr<example::Person> >(db, example::Person::Id.in(sel) && expr);
}
litesql::DataSource<litesql::PersistentPtr<example::Person> > PersonPersonRelationFather::getPerson2(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Person2.fullName());
    sel.where(srcExpr);
    return litesql::DataSource<litesql::PersistentPtr<example::Person> >(db, example::Person::Id.in(sel) && expr);
}
PersonPersonRelationSiblings::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : person2(PersonPersonRelationSiblings::Person2), person1(PersonPersonRelationSiblings::Person1) {
    switch(rec.size()) {
    case 2:
        person2 = rec[1];
    case 1:
        person1 = rec[0];
    }
}
const std::string PersonPersonRelationSiblings::table__("Person_Person_Siblings");
const litesql::FieldType PersonPersonRelationSiblings::Person1("Person1","INTEGER",table__);
const litesql::FieldType PersonPersonRelationSiblings::Person2("Person2","INTEGER",table__);
void PersonPersonRelationSiblings::link(const litesql::Database& db, const example::Person& o0, const example::Person& o1) {
    Record values;
    Split fields;
    fields.push_back(Person1.name());
    values.push_back(o0.id);
    fields.push_back(Person2.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
    fields.clear();
    values.clear();
    fields.push_back(Person1.name());
    values.push_back(o1.id);
    fields.push_back(Person2.name());
    values.push_back(o0.id);
    db.insert(table__, values, fields);
}
void PersonPersonRelationSiblings::unlink(const litesql::Database& db, const example::Person& o0, const example::Person& o1) {
    db.delete_(table__, (Person1 == o0.id && Person2 == o1.id));
    db.delete_(table__, (Person1 == o1.id && Person2 == o0.id));
}
void PersonPersonRelationSiblings::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<PersonPersonRelationSiblings::Row> PersonPersonRelationSiblings::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Person1.fullName());
    sel.result(Person2.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<PersonPersonRelationSiblings::Row>(db, sel);
}
litesql::DataSource<litesql::PersistentPtr<example::Person> > PersonPersonRelationSiblings::getPerson1(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Person1.fullName());
    sel.where(srcExpr);
    return litesql::DataSource<litesql::PersistentPtr<example::Person> >(db, example::Person::Id.in(sel) && expr);
}
litesql::DataSource<litesql::PersistentPtr<example::Person> > PersonPersonRelationSiblings::getPerson2(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Person2.fullName());
    sel.where(srcExpr);
    return litesql::DataSource<litesql::PersistentPtr<example::Person> >(db, example::Person::Id.in(sel) && expr);
}
PersonPersonRelationChildren::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : person2(PersonPersonRelationChildren::Person2), person1(PersonPersonRelationChildren::Person1) {
    switch(rec.size()) {
    case 2:
        person2 = rec[1];
    case 1:
        person1 = rec[0];
    }
}
const std::string PersonPersonRelationChildren::table__("Person_Person_Children");
const litesql::FieldType PersonPersonRelationChildren::Person1("Person1","INTEGER",table__);
const litesql::FieldType PersonPersonRelationChildren::Person2("Person2","INTEGER",table__);
void PersonPersonRelationChildren::link(const litesql::Database& db, const example::Person& o0, const example::Person& o1) {
    Record values;
    Split fields;
    fields.push_back(Person1.name());
    values.push_back(o0.id);
    fields.push_back(Person2.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void PersonPersonRelationChildren::unlink(const litesql::Database& db, const example::Person& o0, const example::Person& o1) {
    db.delete_(table__, (Person1 == o0.id && Person2 == o1.id));
}
void PersonPersonRelationChildren::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<PersonPersonRelationChildren::Row> PersonPersonRelationChildren::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Person1.fullName());
    sel.result(Person2.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<PersonPersonRelationChildren::Row>(db, sel);
}
litesql::DataSource<litesql::PersistentPtr<example::Person> > PersonPersonRelationChildren::getPerson1(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Person1.fullName());
    sel.where(srcExpr);
    return litesql::DataSource<litesql::PersistentPtr<example::Person> >(db, example::Person::Id.in(sel) && expr);
}
litesql::DataSource<litesql::PersistentPtr<example::Person> > PersonPersonRelationChildren::getPerson2(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Person2.fullName());
    sel.where(srcExpr);
    return litesql::DataSource<litesql::PersistentPtr<example::Person> >(db, example::Person::Id.in(sel) && expr);
}
RoleRelation::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : role(RoleRelation::Role), person(RoleRelation::Person) {
    switch(rec.size()) {
    case 2:
        role = rec[1];
    case 1:
        person = rec[0];
    }
}
const std::string RoleRelation::table__("Person_Role_Roles");
const litesql::FieldType RoleRelation::Person("Person1","INTEGER",table__);
const litesql::FieldType RoleRelation::Role("Role2","INTEGER",table__);
void RoleRelation::link(const litesql::Database& db, const example::Person& o0, const example::Role& o1) {
    Record values;
    Split fields;
    fields.push_back(Person.name());
    values.push_back(o0.id);
    fields.push_back(Role.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void RoleRelation::unlink(const litesql::Database& db, const example::Person& o0, const example::Role& o1) {
    db.delete_(table__, (Person == o0.id && Role == o1.id));
}
void RoleRelation::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<RoleRelation::Row> RoleRelation::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Person.fullName());
    sel.result(Role.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<RoleRelation::Row>(db, sel);
}
template <> litesql::DataSource<litesql::PersistentPtr<example::Person> > RoleRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Person.fullName());
    sel.where(srcExpr);
    return litesql::DataSource<litesql::PersistentPtr<example::Person> >(db, example::Person::Id.in(sel) && expr);
}
template <> litesql::DataSource<litesql::PersistentPtr<example::Role> > RoleRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Role.fullName());
    sel.where(srcExpr);
    return litesql::DataSource<litesql::PersistentPtr<example::Role> >(db, example::Role::Id.in(sel) && expr);
}
SchoolStudentRelation::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : student(SchoolStudentRelation::Student), school(SchoolStudentRelation::School) {
    switch(rec.size()) {
    case 2:
        student = rec[1];
    case 1:
        school = rec[0];
    }
}
const std::string SchoolStudentRelation::table__("School_Student_");
const litesql::FieldType SchoolStudentRelation::School("School1","INTEGER",table__);
const litesql::FieldType SchoolStudentRelation::Student("Student2","INTEGER",table__);
void SchoolStudentRelation::link(const litesql::Database& db, const example::School& o0, const example::Student& o1) {
    Record values;
    Split fields;
    fields.push_back(School.name());
    values.push_back(o0.id);
    fields.push_back(Student.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void SchoolStudentRelation::unlink(const litesql::Database& db, const example::School& o0, const example::Student& o1) {
    db.delete_(table__, (School == o0.id && Student == o1.id));
}
void SchoolStudentRelation::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<SchoolStudentRelation::Row> SchoolStudentRelation::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(School.fullName());
    sel.result(Student.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<SchoolStudentRelation::Row>(db, sel);
}
template <> litesql::DataSource<litesql::PersistentPtr<example::School> > SchoolStudentRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(School.fullName());
    sel.where(srcExpr);
    return litesql::DataSource<litesql::PersistentPtr<example::School> >(db, example::School::Id.in(sel) && expr);
}
template <> litesql::DataSource<litesql::PersistentPtr<example::Student> > SchoolStudentRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Student.fullName());
    sel.where(srcExpr);
    return litesql::DataSource<litesql::PersistentPtr<example::Student> >(db, example::Student::Id.in(sel) && expr);
}
EmployeeOfficeRelation::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : office(EmployeeOfficeRelation::Office), employee(EmployeeOfficeRelation::Employee) {
    switch(rec.size()) {
    case 2:
        office = rec[1];
    case 1:
        employee = rec[0];
    }
}
const std::string EmployeeOfficeRelation::table__("Employee_Office_");
const litesql::FieldType EmployeeOfficeRelation::Employee("Employee1","INTEGER",table__);
const litesql::FieldType EmployeeOfficeRelation::Office("Office2","INTEGER",table__);
void EmployeeOfficeRelation::link(const litesql::Database& db, const example::Employee& o0, const example::Office& o1) {
    Record values;
    Split fields;
    fields.push_back(Employee.name());
    values.push_back(o0.id);
    fields.push_back(Office.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void EmployeeOfficeRelation::unlink(const litesql::Database& db, const example::Employee& o0, const example::Office& o1) {
    db.delete_(table__, (Employee == o0.id && Office == o1.id));
}
void EmployeeOfficeRelation::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<EmployeeOfficeRelation::Row> EmployeeOfficeRelation::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Employee.fullName());
    sel.result(Office.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<EmployeeOfficeRelation::Row>(db, sel);
}
template <> litesql::DataSource<litesql::PersistentPtr<example::Employee> > EmployeeOfficeRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Employee.fullName());
    sel.where(srcExpr);
    return litesql::DataSource<litesql::PersistentPtr<example::Employee> >(db, example::Employee::Id.in(sel) && expr);
}
template <> litesql::DataSource<litesql::PersistentPtr<example::Office> > EmployeeOfficeRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Office.fullName());
    sel.where(srcExpr);
    return litesql::DataSource<litesql::PersistentPtr<example::Office> >(db, example::Office::Id.in(sel) && expr);
}
const litesql::FieldType user::Own::Id("id_","INTEGER","user_");
const std::string user::type__("user");
const std::string user::table__("user_");
const std::string user::sequence__("user_seq");
const litesql::FieldType user::Id("id_","INTEGER",table__);
const litesql::FieldType user::Type("type_","TEXT",table__);
const litesql::FieldType user::Name("name_","TEXT",table__);
const litesql::FieldType user::Passwd("passwd_","TEXT",table__);
void user::defaults() {
    id = 0;
}
user::user(const litesql::Database& db, const std::string& type)
     : litesql::Persistent(db, type, Id), name(Name), passwd(Passwd) {
    defaults();
}
user::user(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec, Id), name(Name), passwd(Passwd) {
    const string *flds = NULL;
    Records recs;
    if (rec.size() >= 4) {
        flds = &rec[2];
    } else {
        recs = db.query("SELECT name_, passwd_ FROM user_ WHERE id_="  + (string)id);
        if (recs.size() > 0) {
            flds = &recs[0][0];
        }
    }
    name = convert<const std::string&, std::string>(flds[0]);
    name.setModified(false);
    passwd = convert<const std::string&, std::string>(flds[1]);
    passwd.setModified(false);
}
std::string user::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back("id_");
    values.push_back(id);
    fields.push_back("type_");
    values.push_back(getType());
    fields.push_back(name.name());
    values.push_back(name);
    name.setModified(false);
    fields.push_back(passwd.name());
    values.push_back(passwd);
    passwd.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void user::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void user::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, name);
    updateField(updates, table__, passwd);
}
void user::addIDUpdates(Updates& updates) {
}
void user::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(Name);
    ftypes.push_back(Passwd);
}
void user::delRecord() {
    deleteFromTable(table__, id);
    litesql::Persistent::delRecord();
}
void user::delRelations() {
}
void user::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void user::del() {
    onDelete();
    delRecord();
    inDatabase = false;
}
bool user::typeIsCorrect() {
    return true;
}
std::ostream & operator<<(std::ostream& os, const user& o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << "type_ = " << o.getType() << std::endl;
    os << o.name.name() << " = " << o.name << std::endl;
    os << o.passwd.name() << " = " << o.passwd << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Person::Own::Id("id_","INTEGER","Person_");
const int Person::SexType::Male(0);
const int Person::SexType::Female(1);
Person::SexType::SexType(const std::string& n, const std::string& t, const std::string& tbl, const litesql::FieldType::Values& vals)
         : litesql::FieldType(n,t,tbl,vals) {
}
const int Person::Sex::Male(0);
const int Person::Sex::Female(1);
Person::MotherHandle::MotherHandle(const Person& owner)
         : litesql::RelationHandle<Person>(owner) {
}
void Person::MotherHandle::link(const Person& o0, int intfld) {
    PersonPersonRelationMother::link(owner->getDatabase(), *owner, o0, intfld);
}
void Person::MotherHandle::unlink(const Person& o0) {
    PersonPersonRelationMother::unlink(owner->getDatabase(), *owner, o0);
}
void Person::MotherHandle::del(const litesql::Expr& expr) {
    PersonPersonRelationMother::del(owner->getDatabase(), expr && PersonPersonRelationMother::Person1 == owner->id);
}
litesql::DataSource<litesql::PersistentPtr<Person> > Person::MotherHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return PersonPersonRelationMother::getPerson2(owner->getDatabase(), expr, (PersonPersonRelationMother::Person1 == owner->id) && srcExpr);
}
litesql::DataSource<PersonPersonRelationMother::Row> Person::MotherHandle::getRows(const litesql::Expr& expr) {
    return PersonPersonRelationMother::getRows(owner->getDatabase(), expr && (PersonPersonRelationMother::Person1 == owner->id));
}
Person::FatherHandle::FatherHandle(const Person& owner)
         : litesql::RelationHandle<Person>(owner) {
}
void Person::FatherHandle::link(const Person& o0) {
    PersonPersonRelationFather::link(owner->getDatabase(), *owner, o0);
}
void Person::FatherHandle::unlink(const Person& o0) {
    PersonPersonRelationFather::unlink(owner->getDatabase(), *owner, o0);
}
void Person::FatherHandle::del(const litesql::Expr& expr) {
    PersonPersonRelationFather::del(owner->getDatabase(), expr && PersonPersonRelationFather::Person1 == owner->id);
}
litesql::DataSource<litesql::PersistentPtr<Person> > Person::FatherHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return PersonPersonRelationFather::getPerson2(owner->getDatabase(), expr, (PersonPersonRelationFather::Person1 == owner->id) && srcExpr);
}
litesql::DataSource<PersonPersonRelationFather::Row> Person::FatherHandle::getRows(const litesql::Expr& expr) {
    return PersonPersonRelationFather::getRows(owner->getDatabase(), expr && (PersonPersonRelationFather::Person1 == owner->id));
}
Person::SiblingsHandle::SiblingsHandle(const Person& owner)
         : litesql::RelationHandle<Person>(owner) {
}
void Person::SiblingsHandle::link(const Person& o0) {
    PersonPersonRelationSiblings::link(owner->getDatabase(), *owner, o0);
}
void Person::SiblingsHandle::unlink(const Person& o0) {
    PersonPersonRelationSiblings::unlink(owner->getDatabase(), *owner, o0);
}
void Person::SiblingsHandle::del(const litesql::Expr& expr) {
    PersonPersonRelationSiblings::del(owner->getDatabase(), expr && PersonPersonRelationSiblings::Person1 == owner->id);
}
litesql::DataSource<litesql::PersistentPtr<Person> > Person::SiblingsHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return PersonPersonRelationSiblings::getPerson2(owner->getDatabase(), expr, (PersonPersonRelationSiblings::Person1 == owner->id) && srcExpr);
}
litesql::DataSource<PersonPersonRelationSiblings::Row> Person::SiblingsHandle::getRows(const litesql::Expr& expr) {
    return PersonPersonRelationSiblings::getRows(owner->getDatabase(), expr && (PersonPersonRelationSiblings::Person1 == owner->id));
}
Person::ChildrenHandle::ChildrenHandle(const Person& owner)
         : litesql::RelationHandle<Person>(owner) {
}
void Person::ChildrenHandle::link(const Person& o0) {
    PersonPersonRelationChildren::link(owner->getDatabase(), *owner, o0);
}
void Person::ChildrenHandle::unlink(const Person& o0) {
    PersonPersonRelationChildren::unlink(owner->getDatabase(), *owner, o0);
}
void Person::ChildrenHandle::del(const litesql::Expr& expr) {
    PersonPersonRelationChildren::del(owner->getDatabase(), expr && PersonPersonRelationChildren::Person1 == owner->id);
}
litesql::DataSource<litesql::PersistentPtr<Person> > Person::ChildrenHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return PersonPersonRelationChildren::getPerson2(owner->getDatabase(), expr, (PersonPersonRelationChildren::Person1 == owner->id) && srcExpr);
}
litesql::DataSource<PersonPersonRelationChildren::Row> Person::ChildrenHandle::getRows(const litesql::Expr& expr) {
    return PersonPersonRelationChildren::getRows(owner->getDatabase(), expr && (PersonPersonRelationChildren::Person1 == owner->id));
}
Person::RolesHandle::RolesHandle(const Person& owner)
         : litesql::RelationHandle<Person>(owner) {
}
void Person::RolesHandle::link(const Role& o0) {
    RoleRelation::link(owner->getDatabase(), *owner, o0);
}
void Person::RolesHandle::unlink(const Role& o0) {
    RoleRelation::unlink(owner->getDatabase(), *owner, o0);
}
void Person::RolesHandle::del(const litesql::Expr& expr) {
    RoleRelation::del(owner->getDatabase(), expr && RoleRelation::Person == owner->id);
}
litesql::DataSource<litesql::PersistentPtr<Role> > Person::RolesHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return RoleRelation::get<litesql::PersistentPtr<Role> >(owner->getDatabase(), expr, (RoleRelation::Person == owner->id) && srcExpr);
}
litesql::DataSource<RoleRelation::Row> Person::RolesHandle::getRows(const litesql::Expr& expr) {
    return RoleRelation::getRows(owner->getDatabase(), expr && (RoleRelation::Person == owner->id));
}
const std::string Person::type__("Person");
const std::string Person::table__("Person_");
const std::string Person::sequence__("Person_seq");
const litesql::FieldType Person::Id("id_","INTEGER",table__);
const litesql::FieldType Person::Type("type_","TEXT",table__);
const litesql::FieldType Person::Name("name_","TEXT",table__);
const litesql::FieldType Person::Age("age_","INTEGER",table__);
const litesql::FieldType Person::Image("image_","BLOB",table__);
std::vector < std::pair< std::string, std::string > > Person::sex_values;
const Person::SexType Person::Sex("sex_","INTEGER",table__,sex_values);
void Person::initValues() {
    sex_values.clear();
    sex_values.push_back(make_pair<std::string, std::string>("Male","0"));
    sex_values.push_back(make_pair<std::string, std::string>("Female","1"));
}
void Person::defaults() {
    id = 0;
    age = 15;
    image = 0;
    sex = 0;
}
Person::Person(const litesql::Database& db, const std::string& type)
     : litesql::Persistent(db, type, Id), name(Name), age(Age), image(Image), sex(Sex) {
    defaults();
}
Person::Person(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec, Id), name(Name), age(Age), image(Image), sex(Sex) {
    const string *flds = NULL;
    Records recs;
    if (rec.size() >= 6) {
        flds = &rec[2];
    } else {
        recs = db.query("SELECT name_, age_, image_, sex_ FROM Person_ WHERE id_="  + (string)id);
        if (recs.size() > 0) {
            flds = &recs[0][0];
        }
    }
    name = convert<const std::string&, std::string>(flds[0]);
    name.setModified(false);
    age = convert<const std::string&, int>(flds[1]);
    age.setModified(false);
    image = convert<const std::string&, litesql::Blob>(flds[2]);
    image.setModified(false);
    sex = convert<const std::string&, int>(flds[3]);
    sex.setModified(false);
}
Person::MotherHandle Person::mother() {
    return Person::MotherHandle(*this);
}
Person::FatherHandle Person::father() {
    return Person::FatherHandle(*this);
}
Person::SiblingsHandle Person::siblings() {
    return Person::SiblingsHandle(*this);
}
Person::ChildrenHandle Person::children() {
    return Person::ChildrenHandle(*this);
}
Person::RolesHandle Person::roles() {
    return Person::RolesHandle(*this);
}
std::string Person::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back("id_");
    values.push_back(id);
    fields.push_back("type_");
    values.push_back(getType());
    fields.push_back(name.name());
    values.push_back(name);
    name.setModified(false);
    fields.push_back(age.name());
    values.push_back(age);
    age.setModified(false);
    fields.push_back(image.name());
    values.push_back(image);
    image.setModified(false);
    fields.push_back(sex.name());
    values.push_back(sex);
    sex.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Person::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Person::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, name);
    updateField(updates, table__, age);
    updateField(updates, table__, image);
    updateField(updates, table__, sex);
}
void Person::addIDUpdates(Updates& updates) {
}
void Person::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(Name);
    ftypes.push_back(Age);
    ftypes.push_back(Image);
    ftypes.push_back(Sex);
}
void Person::delRecord() {
    deleteFromTable(table__, id);
    litesql::Persistent::delRecord();
}
void Person::delRelations() {
    RoleRelation::del(*db, (RoleRelation::Person == id));
    PersonPersonRelationMother::del(*db, (PersonPersonRelationMother::Person1 == id) || (PersonPersonRelationMother::Person2 == id));
    PersonPersonRelationFather::del(*db, (PersonPersonRelationFather::Person1 == id) || (PersonPersonRelationFather::Person2 == id));
    PersonPersonRelationSiblings::del(*db, (PersonPersonRelationSiblings::Person1 == id) || (PersonPersonRelationSiblings::Person2 == id));
    PersonPersonRelationChildren::del(*db, (PersonPersonRelationChildren::Person1 == id) || (PersonPersonRelationChildren::Person2 == id));
}
void Person::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Person::del() {
    onDelete();
    delRecord();
    inDatabase = false;
}
bool Person::typeIsCorrect() {
    return true;
}
std::ostream & operator<<(std::ostream& os, const Person& o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << "type_ = " << o.getType() << std::endl;
    os << o.name.name() << " = " << o.name << std::endl;
    os << o.age.name() << " = " << o.age << std::endl;
    os << o.image.name() << " = " << o.image << std::endl;
    os << o.sex.name() << " = " << o.sex << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Role::Own::Id("id_","INTEGER","Role_");
Role::PersonHandle::PersonHandle(const Role& owner)
         : litesql::RelationHandle<Role>(owner) {
}
void Role::PersonHandle::link(const Person& o0) {
    RoleRelation::link(owner->getDatabase(), o0, *owner);
}
void Role::PersonHandle::unlink(const Person& o0) {
    RoleRelation::unlink(owner->getDatabase(), o0, *owner);
}
void Role::PersonHandle::del(const litesql::Expr& expr) {
    RoleRelation::del(owner->getDatabase(), expr && RoleRelation::Role == owner->id);
}
litesql::DataSource<litesql::PersistentPtr<Person> > Role::PersonHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return RoleRelation::get<litesql::PersistentPtr<Person> >(owner->getDatabase(), expr, (RoleRelation::Role == owner->id) && srcExpr);
}
litesql::DataSource<RoleRelation::Row> Role::PersonHandle::getRows(const litesql::Expr& expr) {
    return RoleRelation::getRows(owner->getDatabase(), expr && (RoleRelation::Role == owner->id));
}
const std::string Role::type__("Role");
const std::string Role::table__("Role_");
const std::string Role::sequence__("Role_seq");
const litesql::FieldType Role::Id("id_","INTEGER",table__);
const litesql::FieldType Role::Type("type_","TEXT",table__);
void Role::defaults() {
    id = 0;
}
Role::Role(const litesql::Database& db, const std::string& type)
     : litesql::Persistent(db, type, Id) {
    defaults();
}
Role::Role(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec, Id) {
}
Role::PersonHandle Role::person() {
    return Role::PersonHandle(*this);
}
std::string Role::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back("id_");
    values.push_back(id);
    fields.push_back("type_");
    values.push_back(getType());
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Role::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Role::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
}
void Role::addIDUpdates(Updates& updates) {
}
void Role::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
}
void Role::delRecord() {
    deleteFromTable(table__, id);
    litesql::Persistent::delRecord();
}
void Role::delRelations() {
    RoleRelation::del(*db, (RoleRelation::Role == id));
}
void Role::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Role::del() {
    onDelete();
    delRecord();
    inDatabase = false;
}
bool Role::typeIsCorrect() {
    return true;
}
std::ostream & operator<<(std::ostream& os, const Role& o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << "type_ = " << o.getType() << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Student::Own::Id("id_","INTEGER","Student_");
Student::SchoolHandle::SchoolHandle(const Student& owner)
         : litesql::RelationHandle<Student>(owner) {
}
void Student::SchoolHandle::link(const School& o0) {
    SchoolStudentRelation::link(owner->getDatabase(), o0, *owner);
}
void Student::SchoolHandle::unlink(const School& o0) {
    SchoolStudentRelation::unlink(owner->getDatabase(), o0, *owner);
}
void Student::SchoolHandle::del(const litesql::Expr& expr) {
    SchoolStudentRelation::del(owner->getDatabase(), expr && SchoolStudentRelation::Student == owner->id);
}
litesql::DataSource<litesql::PersistentPtr<School> > Student::SchoolHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return SchoolStudentRelation::get<litesql::PersistentPtr<School> >(owner->getDatabase(), expr, (SchoolStudentRelation::Student == owner->id) && srcExpr);
}
litesql::DataSource<SchoolStudentRelation::Row> Student::SchoolHandle::getRows(const litesql::Expr& expr) {
    return SchoolStudentRelation::getRows(owner->getDatabase(), expr && (SchoolStudentRelation::Student == owner->id));
}
const std::string Student::type__("Student");
const std::string Student::table__("Student_");
Student::Student(const litesql::Database& db, const std::string& type)
     : Role(db, type) {
}
Student::Student(const litesql::Database& db, const litesql::Record& rec)
     : Role(db, rec) {
}
Student::SchoolHandle Student::school() {
    return Student::SchoolHandle(*this);
}
std::string Student::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back("id_");
    values.push_back(id);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return Role::insert(tables, fieldRecs, valueRecs);
}
void Student::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Student::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    Role::addUpdates(updates);
}
void Student::addIDUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
}
void Student::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    Role::getFieldTypes(ftypes);
}
void Student::delRecord() {
    deleteFromTable(table__, id);
    Role::delRecord();
}
void Student::delRelations() {
    SchoolStudentRelation::del(*db, (SchoolStudentRelation::Student == id));
}
void Student::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Student::del() {
    onDelete();
    delRecord();
    inDatabase = false;
}
bool Student::typeIsCorrect() {
    return true;
}
std::ostream & operator<<(std::ostream& os, const Student& o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << "type_ = " << o.getType() << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Employee::Own::Id("id_","INTEGER","Employee_");
Employee::OfficeHandle::OfficeHandle(const Employee& owner)
         : litesql::RelationHandle<Employee>(owner) {
}
void Employee::OfficeHandle::link(const Office& o0) {
    EmployeeOfficeRelation::link(owner->getDatabase(), *owner, o0);
}
void Employee::OfficeHandle::unlink(const Office& o0) {
    EmployeeOfficeRelation::unlink(owner->getDatabase(), *owner, o0);
}
void Employee::OfficeHandle::del(const litesql::Expr& expr) {
    EmployeeOfficeRelation::del(owner->getDatabase(), expr && EmployeeOfficeRelation::Employee == owner->id);
}
litesql::DataSource<litesql::PersistentPtr<Office> > Employee::OfficeHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return EmployeeOfficeRelation::get<litesql::PersistentPtr<Office> >(owner->getDatabase(), expr, (EmployeeOfficeRelation::Employee == owner->id) && srcExpr);
}
litesql::DataSource<EmployeeOfficeRelation::Row> Employee::OfficeHandle::getRows(const litesql::Expr& expr) {
    return EmployeeOfficeRelation::getRows(owner->getDatabase(), expr && (EmployeeOfficeRelation::Employee == owner->id));
}
const std::string Employee::type__("Employee");
const std::string Employee::table__("Employee_");
Employee::Employee(const litesql::Database& db, const std::string& type)
     : Role(db, type) {
}
Employee::Employee(const litesql::Database& db, const litesql::Record& rec)
     : Role(db, rec) {
}
Employee::OfficeHandle Employee::office() {
    return Employee::OfficeHandle(*this);
}
std::string Employee::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back("id_");
    values.push_back(id);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return Role::insert(tables, fieldRecs, valueRecs);
}
void Employee::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Employee::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    Role::addUpdates(updates);
}
void Employee::addIDUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
}
void Employee::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    Role::getFieldTypes(ftypes);
}
void Employee::delRecord() {
    deleteFromTable(table__, id);
    Role::delRecord();
}
void Employee::delRelations() {
    EmployeeOfficeRelation::del(*db, (EmployeeOfficeRelation::Employee == id));
}
void Employee::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Employee::del() {
    onDelete();
    delRecord();
    inDatabase = false;
}
bool Employee::typeIsCorrect() {
    return true;
}
std::ostream & operator<<(std::ostream& os, const Employee& o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << "type_ = " << o.getType() << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType School::Own::Id("id_","INTEGER","School_");
School::StudentsHandle::StudentsHandle(const School& owner)
         : litesql::RelationHandle<School>(owner) {
}
void School::StudentsHandle::link(const Student& o0) {
    SchoolStudentRelation::link(owner->getDatabase(), *owner, o0);
}
void School::StudentsHandle::unlink(const Student& o0) {
    SchoolStudentRelation::unlink(owner->getDatabase(), *owner, o0);
}
void School::StudentsHandle::del(const litesql::Expr& expr) {
    SchoolStudentRelation::del(owner->getDatabase(), expr && SchoolStudentRelation::School == owner->id);
}
litesql::DataSource<litesql::PersistentPtr<Student> > School::StudentsHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return SchoolStudentRelation::get<litesql::PersistentPtr<Student> >(owner->getDatabase(), expr, (SchoolStudentRelation::School == owner->id) && srcExpr);
}
litesql::DataSource<SchoolStudentRelation::Row> School::StudentsHandle::getRows(const litesql::Expr& expr) {
    return SchoolStudentRelation::getRows(owner->getDatabase(), expr && (SchoolStudentRelation::School == owner->id));
}
const std::string School::type__("School");
const std::string School::table__("School_");
const std::string School::sequence__("School_seq");
const litesql::FieldType School::Id("id_","INTEGER",table__);
const litesql::FieldType School::Type("type_","TEXT",table__);
const litesql::FieldType School::Name("name_","TEXT",table__);
void School::defaults() {
    id = 0;
}
School::School(const litesql::Database& db, const std::string& type)
     : litesql::Persistent(db, type, Id), name(Name) {
    defaults();
}
School::School(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec, Id), name(Name) {
    const string *flds = NULL;
    Records recs;
    if (rec.size() >= 3) {
        flds = &rec[2];
    } else {
        recs = db.query("SELECT name_ FROM School_ WHERE id_="  + (string)id);
        if (recs.size() > 0) {
            flds = &recs[0][0];
        }
    }
    name = convert<const std::string&, std::string>(flds[0]);
    name.setModified(false);
}
School::StudentsHandle School::students() {
    return School::StudentsHandle(*this);
}
std::string School::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back("id_");
    values.push_back(id);
    fields.push_back("type_");
    values.push_back(getType());
    fields.push_back(name.name());
    values.push_back(name);
    name.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void School::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void School::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, name);
}
void School::addIDUpdates(Updates& updates) {
}
void School::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(Name);
}
void School::delRecord() {
    deleteFromTable(table__, id);
    litesql::Persistent::delRecord();
}
void School::delRelations() {
    SchoolStudentRelation::del(*db, (SchoolStudentRelation::School == id));
}
void School::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void School::del() {
    onDelete();
    delRecord();
    inDatabase = false;
}
bool School::typeIsCorrect() {
    return true;
}
std::ostream & operator<<(std::ostream& os, const School& o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << "type_ = " << o.getType() << std::endl;
    os << o.name.name() << " = " << o.name << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Office::Own::Id("id_","INTEGER","Office_");
Office::EmployeesHandle::EmployeesHandle(const Office& owner)
         : litesql::RelationHandle<Office>(owner) {
}
void Office::EmployeesHandle::link(const Employee& o0) {
    EmployeeOfficeRelation::link(owner->getDatabase(), o0, *owner);
}
void Office::EmployeesHandle::unlink(const Employee& o0) {
    EmployeeOfficeRelation::unlink(owner->getDatabase(), o0, *owner);
}
void Office::EmployeesHandle::del(const litesql::Expr& expr) {
    EmployeeOfficeRelation::del(owner->getDatabase(), expr && EmployeeOfficeRelation::Office == owner->id);
}
litesql::DataSource<litesql::PersistentPtr<Employee> > Office::EmployeesHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return EmployeeOfficeRelation::get<litesql::PersistentPtr<Employee> >(owner->getDatabase(), expr, (EmployeeOfficeRelation::Office == owner->id) && srcExpr);
}
litesql::DataSource<EmployeeOfficeRelation::Row> Office::EmployeesHandle::getRows(const litesql::Expr& expr) {
    return EmployeeOfficeRelation::getRows(owner->getDatabase(), expr && (EmployeeOfficeRelation::Office == owner->id));
}
const std::string Office::type__("Office");
const std::string Office::table__("Office_");
const std::string Office::sequence__("Office_seq");
const litesql::FieldType Office::Id("id_","INTEGER",table__);
const litesql::FieldType Office::Type("type_","TEXT",table__);
void Office::defaults() {
    id = 0;
}
Office::Office(const litesql::Database& db, const std::string& type)
     : litesql::Persistent(db, type, Id) {
    defaults();
}
Office::Office(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec, Id) {
}
Office::EmployeesHandle Office::employees() {
    return Office::EmployeesHandle(*this);
}
std::string Office::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back("id_");
    values.push_back(id);
    fields.push_back("type_");
    values.push_back(getType());
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void Office::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Office::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
}
void Office::addIDUpdates(Updates& updates) {
}
void Office::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
}
void Office::delRecord() {
    deleteFromTable(table__, id);
    litesql::Persistent::delRecord();
}
void Office::delRelations() {
    EmployeeOfficeRelation::del(*db, (EmployeeOfficeRelation::Office == id));
}
void Office::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Office::del() {
    onDelete();
    delRecord();
    inDatabase = false;
}
bool Office::typeIsCorrect() {
    return true;
}
std::ostream & operator<<(std::ostream& os, const Office& o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << "type_ = " << o.getType() << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
ExampleDatabase::ExampleDatabase(std::string backendType, std::string connInfo)
     : litesql::Database(backendType, connInfo) {
    initialize();
}
std::vector<litesql::Database::SchemaItem> ExampleDatabase::getSchema() const {
    vector<Database::SchemaItem> res;
    res.push_back(Database::SchemaItem("schema_","table","CREATE TABLE schema_ (name_ TEXT, type_ TEXT, sql_ TEXT);"));
    if (backend->supportsSequences()) {
        res.push_back(Database::SchemaItem("user_seq","sequence","CREATE SEQUENCE user_seq START 1 INCREMENT 1"));
        res.push_back(Database::SchemaItem("Person_seq","sequence","CREATE SEQUENCE Person_seq START 1 INCREMENT 1"));
        res.push_back(Database::SchemaItem("Role_seq","sequence","CREATE SEQUENCE Role_seq START 1 INCREMENT 1"));
        res.push_back(Database::SchemaItem("School_seq","sequence","CREATE SEQUENCE School_seq START 1 INCREMENT 1"));
        res.push_back(Database::SchemaItem("Office_seq","sequence","CREATE SEQUENCE Office_seq START 1 INCREMENT 1"));
    }
    res.push_back(Database::SchemaItem("user_","table","CREATE TABLE user_ (id_ " + backend->getRowIDType() + ",type_ TEXT,name_ TEXT,passwd_ TEXT)"));
    res.push_back(Database::SchemaItem("Person_","table","CREATE TABLE Person_ (id_ " + backend->getRowIDType() + ",type_ TEXT,name_ TEXT,age_ INTEGER,image_ BLOB,sex_ INTEGER)"));
    res.push_back(Database::SchemaItem("Role_","table","CREATE TABLE Role_ (id_ " + backend->getRowIDType() + ",type_ TEXT)"));
    res.push_back(Database::SchemaItem("Student_","table","CREATE TABLE Student_ (id_ " + backend->getRowIDType() + ")"));
    res.push_back(Database::SchemaItem("Employee_","table","CREATE TABLE Employee_ (id_ " + backend->getRowIDType() + ")"));
    res.push_back(Database::SchemaItem("School_","table","CREATE TABLE School_ (id_ " + backend->getRowIDType() + ",type_ TEXT,name_ TEXT)"));
    res.push_back(Database::SchemaItem("Office_","table","CREATE TABLE Office_ (id_ " + backend->getRowIDType() + ",type_ TEXT)"));
    res.push_back(Database::SchemaItem("Person_Person_Mother","table","CREATE TABLE Person_Person_Mother (Person1 INTEGER UNIQUE,Person2 INTEGER,intfld_ INTEGER)"));
    res.push_back(Database::SchemaItem("Person_Person_Father","table","CREATE TABLE Person_Person_Father (Person1 INTEGER UNIQUE,Person2 INTEGER)"));
    res.push_back(Database::SchemaItem("Person_Person_Siblings","table","CREATE TABLE Person_Person_Siblings (Person1 INTEGER,Person2 INTEGER)"));
    res.push_back(Database::SchemaItem("Person_Person_Children","table","CREATE TABLE Person_Person_Children (Person1 INTEGER,Person2 INTEGER)"));
    res.push_back(Database::SchemaItem("Person_Role_Roles","table","CREATE TABLE Person_Role_Roles (Person1 INTEGER,Role2 INTEGER UNIQUE)"));
    res.push_back(Database::SchemaItem("School_Student_","table","CREATE TABLE School_Student_ (School1 INTEGER,Student2 INTEGER UNIQUE)"));
    res.push_back(Database::SchemaItem("Employee_Office_","table","CREATE TABLE Employee_Office_ (Employee1 INTEGER,Office2 INTEGER)"));
    res.push_back(Database::SchemaItem("Person_Person_MotherPerson1idx","index","CREATE INDEX Person_Person_MotherPerson1idx ON Person_Person_Mother (Person1)"));
    res.push_back(Database::SchemaItem("Person_Person_MotherPerson2idx","index","CREATE INDEX Person_Person_MotherPerson2idx ON Person_Person_Mother (Person2)"));
    res.push_back(Database::SchemaItem("Person_Person_Mother_all_idx","index","CREATE INDEX Person_Person_Mother_all_idx ON Person_Person_Mother (Person1,Person2)"));
    res.push_back(Database::SchemaItem("Person_Person_FatherPerson1idx","index","CREATE INDEX Person_Person_FatherPerson1idx ON Person_Person_Father (Person1)"));
    res.push_back(Database::SchemaItem("Person_Person_FatherPerson2idx","index","CREATE INDEX Person_Person_FatherPerson2idx ON Person_Person_Father (Person2)"));
    res.push_back(Database::SchemaItem("Person_Person_Father_all_idx","index","CREATE INDEX Person_Person_Father_all_idx ON Person_Person_Father (Person1,Person2)"));
    res.push_back(Database::SchemaItem("_fc4501d1c1e9cc173fbe356a08a9d12f","index","CREATE INDEX _fc4501d1c1e9cc173fbe356a08a9d12f ON Person_Person_Siblings (Person1)"));
    res.push_back(Database::SchemaItem("_29908e51ecc673e39c38238d4abe5b3b","index","CREATE INDEX _29908e51ecc673e39c38238d4abe5b3b ON Person_Person_Siblings (Person2)"));
    res.push_back(Database::SchemaItem("Person_Person_Siblings_all_idx","index","CREATE INDEX Person_Person_Siblings_all_idx ON Person_Person_Siblings (Person1,Person2)"));
    res.push_back(Database::SchemaItem("_c77a0c252bbee950ec06bda52dd09648","index","CREATE INDEX _c77a0c252bbee950ec06bda52dd09648 ON Person_Person_Children (Person1)"));
    res.push_back(Database::SchemaItem("_64f9014350ce47b5d0f7606b127df7c3","index","CREATE INDEX _64f9014350ce47b5d0f7606b127df7c3 ON Person_Person_Children (Person2)"));
    res.push_back(Database::SchemaItem("Person_Person_Children_all_idx","index","CREATE INDEX Person_Person_Children_all_idx ON Person_Person_Children (Person1,Person2)"));
    res.push_back(Database::SchemaItem("Person_Role_RolesPerson1idx","index","CREATE INDEX Person_Role_RolesPerson1idx ON Person_Role_Roles (Person1)"));
    res.push_back(Database::SchemaItem("Person_Role_RolesRole2idx","index","CREATE INDEX Person_Role_RolesRole2idx ON Person_Role_Roles (Role2)"));
    res.push_back(Database::SchemaItem("Person_Role_Roles_all_idx","index","CREATE INDEX Person_Role_Roles_all_idx ON Person_Role_Roles (Person1,Role2)"));
    res.push_back(Database::SchemaItem("School_Student_School1idx","index","CREATE INDEX School_Student_School1idx ON School_Student_ (School1)"));
    res.push_back(Database::SchemaItem("School_Student_Student2idx","index","CREATE INDEX School_Student_Student2idx ON School_Student_ (Student2)"));
    res.push_back(Database::SchemaItem("School_Student__all_idx","index","CREATE INDEX School_Student__all_idx ON School_Student_ (School1,Student2)"));
    res.push_back(Database::SchemaItem("Employee_Office_Employee1idx","index","CREATE INDEX Employee_Office_Employee1idx ON Employee_Office_ (Employee1)"));
    res.push_back(Database::SchemaItem("Employee_Office_Office2idx","index","CREATE INDEX Employee_Office_Office2idx ON Employee_Office_ (Office2)"));
    res.push_back(Database::SchemaItem("Employee_Office__all_idx","index","CREATE INDEX Employee_Office__all_idx ON Employee_Office_ (Employee1,Office2)"));
    return res;
}
void ExampleDatabase::initialize() {
    static bool initialized = false;
    if (initialized)
        return;
    initialized = true;
    Person::initValues();
}
litesql::Persistent* ExampleDatabase::createPersistent(const litesql::Record& rec) const {
    const string &type = rec[1], &id = rec[0];
    Persistent *p = findPersistent(atoi(id.c_str()), type);
    if (p)
    	   return p;
    if (type == "user")
        return new user(*this, rec);
    if (type == "Person")
        return new Person(*this, rec);
    if (type == "Role")
        return new Role(*this, rec);
    if (type == "Student")
        return new Student(*this, rec);
    if (type == "Employee")
        return new Employee(*this, rec);
    if (type == "School")
        return new School(*this, rec);
    if (type == "Office")
        return new Office(*this, rec);
    throw Except("bad type " + type);
}
}
