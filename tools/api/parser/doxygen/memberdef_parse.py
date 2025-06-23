# Copyright 2025 The Lynx Authors. All rights reserved.
# Licensed under the Apache License Version 2.0 that can be found in the
# LICENSE file in the root directory of this source tree.

# /usr/bin/env python3
# -*- coding: utf-8 -*-

from metadata_def import BaseMember, BaseMemberType
from doxmlparser import compound as doxcompound


def function_parse(member_object: BaseMember, memberdef) -> bool:
    member_object.type = BaseMemberType.MethodType
    member_object.definition = (
        f"public {memberdef.get_definition()}{memberdef.get_argsstring()};"
    )
    return True


def variable_parse(member_object: BaseMember, memberdef) -> bool:
    member_object.type = BaseMemberType.VariableType
    member_object.definition = (
        f"public {memberdef.get_definition()} {member_object.name};"
    )
    return True


def property_parse(member_object: BaseMember, memberdef) -> bool:
    member_object.type = BaseMemberType.PropertyType
    member_object.definition = (
        f"public {memberdef.get_definition()} {member_object.name};"
    )
    return True


def typedef_parse(member_object: BaseMember, memberdef) -> bool:
    member_object.type = BaseMemberType.TypedefType
    member_object.definition = memberdef.get_definition()
    return True


def enum_parse(member_object: BaseMember, memberdef) -> bool:
    member_object.type = BaseMemberType.EnumType
    enumvalue_list = memberdef.get_enumvalue()
    member_object.definition = f"public enum {memberdef.get_name()} {{"
    for enumvalue in enumvalue_list:
        member_object.definition += f"\n  {enumvalue.get_name()}"
    member_object.definition += "\n}\n"
    return True


def define_parse(member_object: BaseMember, memberdef) -> bool:
    member_object.type = BaseMemberType.DefineType
    member_object.definition = f"define {memberdef.get_name()}"
    defname_list = memberdef.get_defname()
    member_object.definition += ",".join(defname_list) + "\n"
    initializer_element = memberdef.get_initializer()
    if initializer_element:
        member_object.definition += initializer_element.text + "\n"
    return True


def parse(compounddef, only_public=True) -> list[BaseMember]:
    member_list = []
    for sectiondef in compounddef.get_sectiondef():
        for memberdef in sectiondef.get_memberdef():
            if only_public and memberdef.get_prot() not in [
                doxcompound.DoxProtectionKind.PUBLIC
            ]:
                continue
            memberdef_kind = memberdef.get_kind()
            memberdef_parse_func = MEMBERDEF_PARSE_DICT.get(memberdef_kind)
            if memberdef_parse_func is not None:
                member_object = BaseMember(
                    name=memberdef.get_name(),
                    type=BaseMemberType.UnknownType,
                    brief_desc=memberdef.get_briefdescription(),
                    detailed_desc=memberdef.get_detaileddescription(),
                    definition="",
                )
                if memberdef_parse_func(member_object, memberdef):
                    member_list.append(member_object)
            elif memberdef_kind not in MEMBERDEF_IGNORE_LIST:
                print(f"unknown memberdef: {memberdef_kind}")
    return member_list


MEMBERDEF_PARSE_DICT = {
    doxcompound.DoxMemberKind.FUNCTION: function_parse,
    doxcompound.DoxMemberKind.VARIABLE: variable_parse,
    doxcompound.DoxMemberKind.PROPERTY: property_parse,
    doxcompound.DoxMemberKind.TYPEDEF: typedef_parse,
    doxcompound.DoxMemberKind.ENUM: enum_parse,
}

MEMBERDEF_IGNORE_LIST = [doxcompound.DoxMemberKind.DEFINE]
