---
layout: default
title: Projects 
---

<ul>
  {% for project in site.projects %}
    <li class="post-item">
        <h2><a href="{{ project.url }}">{{ project.name }}</a></h2>
    </li>
  {% endfor %}
</ul>

